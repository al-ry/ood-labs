// stdafx.cpp : source file that includes just the standard includes
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// �������� ���������� boost test, ��� ������� main ����� ������������� ���� (��� ���������������� ���������������� ����������),
// � �� ������������� boost-�� �� ���
#define BOOST_TEST_NO_MAIN
// ���������� ���������� boost test
#pragma warning(push, 3)
#pragma warning(disable : 4702)
#include <boost/test/included/unit_test.hpp>
#pragma warning(pop)
