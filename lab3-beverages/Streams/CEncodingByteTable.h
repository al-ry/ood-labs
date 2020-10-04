#pragma once
#include "stdafx.h"


class CEncodingByteTable
{
public:
	CEncodingByteTable(uint32_t key)
		: m_encryptTable(256)
		, m_decryptTable(256)
	{
		GenerateTables(key);
	}
	uint8_t GetEncrytedByte(uint8_t byte)
	{
		return m_encryptTable[byte];
	}
	uint8_t GetDecrytedByte(uint8_t byte)
	{
		return m_decryptTable[byte];
	}

private: 
	void GenerateTables(uint32_t key)
	{
		std::iota(m_encryptTable.begin(), m_encryptTable.end(), 0);
		std::shuffle(m_encryptTable.begin(), m_encryptTable.end(), std::mt19937(key)); 
		for (size_t i = 0; i < m_encryptTable.size(); i++)
		{
			m_decryptTable[m_encryptTable[i]] = static_cast<uint8_t>(i);
		}
	}
private:
	std::vector<uint8_t> m_encryptTable;
	std::vector<uint8_t> m_decryptTable;
};