#include "stdafx.h"
#include "CMemoryInputStream.h"
#include "COutputFileStream.h"
#include "COutputStreamCompressor.h"
#include "COutputMemoryStream.h"
#include "CEncryptedOutputStream.h"
#include "CFileInputStream.h"
#include "CInputStreamDecompressor.h"
#include "CDecryptedInputStream.h"


enum class OptionType
{
	Encrypt,
	Decrypt,
	Compress,
	Decompress
};

struct SOption
{
	OptionType option;
	std::optional<uint32_t> key;
};

struct StreamsOptions
{
	std::vector<SOption> inputOptions;
	std::vector<SOption> ouputOptions;
};

typedef std::vector<SOption> Options;

StreamsOptions ParseOptions(int argc, char** argv)
{
	StreamsOptions options;
	for (size_t i = 1; i < (size_t)argc; i++)
	{ 
		std::string command = argv[i];
		if (command == "--encrypt")
		{
			options.ouputOptions.push_back(SOption{ OptionType::Encrypt, std::stoul(argv[++i]) });
		}
		else if (command == "--decrypt")
		{
			options.inputOptions.push_back(SOption{ OptionType::Decrypt, std::stoul(argv[++i]) });
		}
		else if (command == "--compress")
		{
			options.ouputOptions.push_back(SOption{ OptionType::Compress, std::nullopt });
		}
		else if (command == "--decompress")
		{
			options.inputOptions.push_back(SOption{ OptionType::Decompress, std::nullopt });
		}
		else
		{
			throw std::runtime_error("Invalid option specified");
		}
	}
	return options;
}

void DecorateInputStream(const Options& options, IInputStreamPtr& inputStream)
{
	for (auto it = options.rbegin(); it != options.rend(); it++)
	{
		if (it->option == OptionType::Decrypt)
		{
			inputStream = std::make_unique<CDecryptedInputStream>(std::move(inputStream), it->key.value());
		}
		else if (it->option == OptionType::Decompress)
		{
			inputStream = std::make_unique<CInputStreamDecompressor>(std::move(inputStream));
		}
	}
}

void DecorateOutputStream(const Options& options, IOutputStreamPtr& outputStream)
{
	for (auto& optn : options)
	{
		if (optn.option == OptionType::Encrypt)
		{
			outputStream = std::make_unique<CEncryptedOutputStream>(std::move(outputStream), optn.key.value());
		}
		else if (optn.option == OptionType::Compress)
		{
			outputStream = std::make_unique<COutputStreamCompressor>(std::move(outputStream));
		}
	}
}

void CopyStreams(IInputStreamPtr& inputStream, IOutputStreamPtr& outputStream)
{
	while (!inputStream->IsEOF())
	{
		try
		{
			uint8_t byte = inputStream->ReadByte();
			outputStream->WriteByte(byte);
		}
		catch (...)
		{
		}
	}
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cout << "Wrong arguments count specified\n"
				  << "Arguments should be:\n"
				  << argv[0] << " [options] <input file> <output file>\n"
				  << "[options]: \n"
				  << "--encrypt <key>\n"
				  << "--decrypt <key>\n"
				  << "--compress\n"
				  << "--decompress\n";
		return 1;
	}
	
	IInputStreamPtr inputStream = std::make_unique<CFileInputStream>(argv[argc - 2]);
	IOutputStreamPtr outputStream = std::make_unique<COutputFileStream>(argv[argc - 1]);
	try
	{
		StreamsOptions options = ParseOptions(argc - 2, argv);

		if (!options.inputOptions.empty())
		{
			DecorateInputStream(options.inputOptions, inputStream);
		}
		if (!options.ouputOptions.empty())
		{
			DecorateOutputStream(options.ouputOptions, outputStream);
		}
	}
	catch (std::invalid_argument&)
	{
		std::cout << "Options <--encrypt> <--decrypt> must contains <key>.";
		return 1;
	}
	catch (std::runtime_error e)
	{
		std::cout << e.what();
		return 1;
	}

	CopyStreams(inputStream, outputStream);
	
	return 0;
}

