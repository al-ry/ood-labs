#include "stdafx.h"
#include "Menu.h"
#include "Document.h"

using namespace std;
using namespace std::placeholders;

namespace
{

class CEditor
{
public:
	CEditor() //-V730
		: m_document(make_unique<CDocument>())
	{
		m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
		m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
		AddMenuItem("setTitle", "Changes title. Args: <new title>", &CEditor::SetTitle);
		AddMenuItem("insertParagraph", "Insert a paragraph in specified position. Args: <position>|end <paragraph text>", &CEditor::InsertParagraph);
		AddMenuItem("insertImage", "Insert a image in specified position. Args: <position>|end <width> <height> <path to image>", &CEditor::InsertImage);
		AddMenuItem("replaceText", "Replace the text in specified position. Args: <position> <text>", &CEditor::ReplaceText);
		AddMenuItem("resizeImage", "Resize the image in specified position. Args: <position> <width> <height>", &CEditor::ResizeImage);
		AddMenuItem("deleteItem", "Delete item in specified position. Args: <position>", &CEditor::DeleteItem);
		AddMenuItem("save", "Save the document. Args: <path>", &CEditor::SaveDocument);
		m_menu.AddItem("list", "Show document", bind(&CEditor::List, this, _1));
		AddMenuItem("undo", "Undo command", &CEditor::Undo);
		AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
	}

	void Start()
	{
		m_menu.Run();
	}

private:
	// Указатель на метод класса CEditor, принимающий istream& и возвращающий void
	typedef void (CEditor::*MenuHandler)(istream& in);

	void AddMenuItem(const string& shortcut, const string& description, MenuHandler handler)
	{
		m_menu.AddItem(shortcut, description, bind(handler, this, _1));
	}

	static boost::optional<size_t> ParsePosition(istream& in)
	{
		string param;
		size_t index;
		in >> param;
		if (param == "end")
		{
			return boost::none;
		}
		stringstream ss(param);
		ss >> index;
		return index;
	}
	void InsertParagraph(istream & in)
	{
		string text;
		boost::optional<size_t> index;
		index = ParsePosition(in);
		std::getline(in, text);		
		try
		{
			m_document->InsertParagraph(text, index);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << endl;
		}
	}

	void ReplaceText(istream& in)
	{
		size_t index;
		string newText;
		try
		{
			in >> index;
			getline(in, newText);
			auto item = m_document->GetItem(index);
			if (!item.GetParagraph())
			{
				throw std::invalid_argument("There is no paragraph in specified position");
			}
			item.GetParagraph()->SetText(newText);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << endl;
		}
	}
	void DeleteItem(istream& in)
	{
		string indexStr;
		size_t index;
		try
		{
			in >> index;
			m_document->DeleteItem(index);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << endl;
		}
	}
	void ResizeImage(istream& in)
	{
		size_t index; 
		try
		{
			in >> index;
			int width;
			int height;
			in >> width;
			in >> height;
			auto item = m_document->GetItem(index);
			if (!item.GetImage())
			{
				throw std::invalid_argument("There is no image in specified position");
			}
			item.GetImage()->Resize(width, height);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << endl;
		}
	}
	void InsertImage(istream& in)
	{
		string param;
		boost::optional<size_t> index;
		index = ParsePosition(in);
		int height;
		int width;
		string path;
		try
		{
			in >> width;
			in >> height;
			in >> path;
			m_document->InsertImage(path, width, height, index);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << endl;
		}
	}
	void SaveDocument(istream& in)
	{
		try
		{
			string savePath;
			in >> savePath;
			m_document->Save(savePath);
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
	}
	void SetTitle(istream& in)
	{
		string head;
		string tail;

		if (in >> head)
		{
			getline(in, tail);
		}
		string title = head + tail;

		m_document->SetTitle(title);
	}

	void List(istream&)
	{
		cout << "-------------" << endl;
		cout << "Title: " << m_document->GetTitle() << endl;
		for (size_t i = 0; i < m_document->GetItemsCount(); i++)
		{
			auto imgPtr = m_document->GetItem(i).GetImage();
			auto phPtr = m_document->GetItem(i).GetParagraph();
			if (imgPtr)
			{
				cout << i << ". Image: " << imgPtr->GetHeight() << " " << imgPtr->GetWidth() << " " << imgPtr->GetPath() << endl;
			}
			else if (phPtr)
			{
				cout << i << ". Paragraph: " << phPtr->GetText() << endl;
			}
		}
		cout << "-------------" << endl;
	}

	void Undo(istream&)
	{
		if (m_document->CanUndo())
		{
			m_document->Undo();
		}
		else
		{
			cout << "Can't undo" << endl;
		}
	}

	void Redo(istream&)
	{
		if (m_document->CanRedo())
		{
			m_document->Redo();
		}
		else
		{
			cout << "Can't redo" << endl;
		}
	}

	CMenu m_menu;
	unique_ptr<IDocument> m_document;
};

} // namespace

int main()
{
	setlocale(LC_ALL, "Russian");
	CEditor editor;
	editor.Start();
	return 0;
}