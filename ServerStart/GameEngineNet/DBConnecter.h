#pragma once
#ifndef UNREALDEFINE
#include <mysql.h>
#include "DBRowData.h"
#include <vector>
#include <GameEngineDebug.h>

#pragma comment(lib, "libmysql")

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class DBConnecter
{
private: // Static Var
public: // Static Func
private: // member Var
    MYSQL* m_DBHandle;
    unsigned __int64 m_affectedRow; // ����� �޾ƺ��� �ִ� ���� ��
    unsigned __int64 m_LastInsertId; // ���� ��Ŭ����Ʈ ����� �޾ƺ� ��

public:
	__int64 GetLastInsertId() 
	{
		return m_LastInsertId;
	}

public: // constructer destructer
    DBConnecter();
    ~DBConnecter();

public: // delete constructer 
    DBConnecter(const DBConnecter& _Other) = delete;
    DBConnecter(const DBConnecter&& _Other) = delete;

public: // delete operator
    DBConnecter& operator=(const DBConnecter& _Other) = delete;
    DBConnecter& operator=(const DBConnecter&& _Other) = delete;

public: // member Func
    void Close();

    bool Connect(const char* _Id, const char* _Password, const char* _SchemaName, int _Port = 3306, const char* _ip = "127.0.0.1");
    bool Ping(unsigned int _Count = 10);
    // ��κ��� ���̳��� ����
    // �� �׳� ���� �־��� ���ڿ� �״���� ������ ����ϴµ�
    // �������� ��������̶�� �͵� �����Ѵ�.
    // �츮�� �����Ҽ� �ִ� ������ �׷��� ���� �ʴ�.
    // ����
    // virtual�� ��������?
    // ���ø��� �����ϴ�.
    // ���ø��� 
    // 100~200 <- ���� �̰� �� db�� �����ϴ°ž�?
    // �ð��� �ؾ��մϴ�.
    // std::vector<std::shared_ptr<DBRowData>>& _Vector ������� �޾ƿ��� �뵵�� �˴ϴ�.
    // ���⼭ ���ø��� ���ųİ� �ְ�.
    bool DynamicQuery(const char* _Query/*, �̰��� ����� �޾ƿ� ��� ������ �ʿ��մϴ�*/);

    template<typename RowDataType>
    bool DynamicQueryTemplate(const char* _Query, std::vector<std::shared_ptr<RowDataType>>& _Vector/*, �̰��� ����� �޾ƿ� ��� ������ �ʿ��մϴ�*/)
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

				// ���� ������ 
				// while�� ������ �� �࿡ �ش��ϴ� 
				// ������ MYSQL_ROW row;�� ��Ƽ� ���� �ִ�.
				// ���� ���ٸ� 
				while (row = mysql_fetch_row(result))
				{
					std::shared_ptr<RowDataType> NewData = std::make_shared<RowDataType>();
					std::vector<DBVar*>& Fields = NewData->GetDBVarData();
					_Vector.push_back(NewData);
					// �� ���� �������� ��.
					++m_affectedRow;
					for (unsigned int i = 0; i < fields; i++)
					{
						Fields[i]->Setting(row[i]);

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

    // ������ �� ���� �����͸� �������� ��Ƽ� �װ͵��� ���������ϰڴ�.

};

#endif