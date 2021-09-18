#include "DBConnecter.h"
#ifndef UNREALDEFINE
#include <GameEngineDebug.h>

// Static Var
// Static Func

// constructer destructer
DBConnecter::DBConnecter() 
{

}

DBConnecter::~DBConnecter() 
{
	Close();
}

bool DBConnecter::Connect(const char* _Id, const char* _Password, const char* _SchemaName, int _Port, const char* _ip)
{
	// c�����ε�.

	// �⺻���� db�ڵ��� ���� ���ӵ��� ����� �����Ҽ� �ְ� ���ش�.
    m_DBHandle = mysql_init(nullptr);

	// CPPMYSQL::MYSQLINIT();

	if (nullptr == m_DBHandle)
	{
		GameEngineDebug::AssertMsg("if (nullptr == m_DBHandle)");
		return false;
	}

	// IStream NewStream;
	// NewStream.open();
	// NewStream << 100;

	// c Ŀ���͸� ����ؼ� c++ Ŀ���͸� ����ϰ� �Ǵµ�.
	// c���̺귯���� c++���̺귯���� ���̴� �����?
	// c++������ ��ü����
	// c������ ��������
	// ��ü������ ��ǥ���� ��Ұ�.

	//MYSQLCPPCONNECT NewCon;
	//NewCon.connect()

	if (0 != mysql_options(m_DBHandle, MYSQL_SET_CHARSET_NAME, "utf8"))
	{
		GameEngineDebug::AssertMsg("if (0 != mysql_options(m_DBHandle, MYSQL_SET_CHARSET_NAME, utf8))");
		return false;
	}


	// CLIENT_MULTI_RESULTS ��� �־����� ������ 
	// Ŀ���͸� �ϳ��� �����ϰ� ����ϰ� ��� ���� ������
	// �ټ��� �����忡�� ó���� �ȵ˴ϴ�.
	// �ѹ��� �ټ��� dbó�� ������� �ޱ� ���ؼ� ����ϴ� �ɼ�
	MYSQL* MySqlConHandle = mysql_real_connect(m_DBHandle, _ip, _Id, _Password, _SchemaName, _Port, nullptr, CLIENT_MULTI_RESULTS);

	if (MySqlConHandle != m_DBHandle)
	{
		const char* Ptr = mysql_error(m_DBHandle);
		GameEngineDebug::AssertMsg("if (0 != mysql_options(m_DBHandle, MYSQL_SET_CHARSET_NAME, utf8))");
		return false;
	}

	bool reconnect = true;

	// db������ ���� �δ� ��찡 �����ϴ�.
	// �ӽ� ���εΰ� db���� ��Ѵ� ���̿���.
	// �� �ɼ��� �ѳ����� mysql_ping �Լ���
	// ��Ŀ��Ʈ�� ���ÿ� ó�����ִ� �Լ��� �˴ϴ�.
	if (0 != mysql_options(m_DBHandle, MYSQL_OPT_RECONNECT, &reconnect))
	{
		// ���� ������ ������ �����ݴϴ�
		const char* Ptr = mysql_error(m_DBHandle);
		GameEngineDebug::AssertMsg(Ptr);
		return false;
	}

	return true;
}

bool DBConnecter::Ping(unsigned int _Count)
{
	// ���� ���� ���� ��� ��ǻ�� ȯ�濡�� �������ִ� ��ɾ �ִµ�
	// �Ϲ������� �� �Լ��� db�� ����ִ����� Ȯ���ϴ� �Լ��� �Ǵµ�.

	for (size_t i = 0; i < _Count; i++)
	{
		if (0 != mysql_ping(m_DBHandle))
		{
			// 
		}
		else 
		{
			// �����ؼ� ������ ���������� ������ �˴ϴ�.
			return true;
		}
	}

	return false;
}


void DBConnecter::Close()
{
	if (nullptr != m_DBHandle)
	{
		mysql_close(m_DBHandle);
		m_DBHandle = nullptr;
	}
}

bool DBConnecter::DynamicQuery(const char* _Query)
{
	m_affectedRow = 0;

	int QueryResult = mysql_query(m_DBHandle, _Query);

	if (0 != QueryResult)
	{
		const char* ErrorText = mysql_error(m_DBHandle);
		GameEngineDebug::AssertMsg(ErrorText);
		return false;
	}

	do 
	{
		// ������� �����ϸ� mysql���� ������� ������ �Լ�
		MYSQL_RES* result = mysql_store_result(m_DBHandle);

		if (nullptr != result)
		{
			// �� �࿡�� ���ϵǴ� ���� ���ü� �ִ� ����ü
			MYSQL_ROW row;
			unsigned int fields = mysql_num_fields(result);

			// while�� ������ �� ���� �ش��ϴ� 
			// ������ MYSQL_ROW row;�� ��Ƽ� ���� �ִ�.
			// ���� ���ٸ� 
			while (row = mysql_fetch_row(result))
			{
				++m_affectedRow;
				for (unsigned int i = 0; i < fields; i++)
				{
					// ���������� �̰����� ���� ��ȯ�� �Ͼ�� �մϴ�.
					
					// _Data.Setting(row[i]);

					// "452112"
					//OutputDebugStringA(row[i]);
					//OutputDebugStringA("\n");
				}
			}

			mysql_free_result(result);
		}
		else 
		{
			if (0 == mysql_field_count(m_DBHandle))
			{
				m_affectedRow += mysql_affected_rows(m_DBHandle);
				// ������ ���� �༮���� �̰����� ó���� �ȴ�.
			}
			else 
			{
				// ���� �׳� ������ ����.
				break;
			}
		}

		QueryResult = mysql_next_result(m_DBHandle);

	} while (0 == QueryResult);

	// �̸� ���ؼ� ������ ���� ��Ŭ����Ʈ(DB�� �������ִ� �ڵ�������) ������
	m_LastInsertId = mysql_insert_id(m_DBHandle);

	return true;
}

// member Func
#endif

