#pragma once
#ifndef UNREALDEFINE
#include <mysql.h>
#include "DBRowData.h"
#include <vector>
#include <GameEngineDebug.h>

#pragma comment(lib, "libmysql")

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class DBConnecter
{
private: // Static Var
public: // Static Func
private: // member Var
    MYSQL* m_DBHandle;
    unsigned __int64 m_affectedRow; // 결과로 받아볼수 있는 열의 수
    unsigned __int64 m_LastInsertId; // 오토 인클리먼트 결과를 받아볼 값

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
    // 대부분이 나이나믹 쿼리
    // 즉 그냥 내가 넣어준 문자열 그대로의 쿼리를 사용하는데
    // 프리페어런스 쿼리방식이라는 것도 존재한다.
    // 우리가 선택할수 있는 수단이 그렇게 많지 않다.
    // 문법
    // virtual은 가능하죠?
    // 템플릿도 가능하다.
    // 템플릿은 
    // 100~200 <- 뭐야 이건 왜 db로 관리하는거야?
    // 시간은 해야합니다.
    // std::vector<std::shared_ptr<DBRowData>>& _Vector 결과물을 받아오는 용도가 됩니다.
    // 여기서 템플릿을 쓸거냐가 있고.
    bool DynamicQuery(const char* _Query/*, 이곳에 결과를 받아올 어떠한 형식이 필요합니다*/);

    template<typename RowDataType>
    bool DynamicQueryTemplate(const char* _Query, std::vector<std::shared_ptr<RowDataType>>& _Vector/*, 이곳에 결과를 받아올 어떠한 형식이 필요합니다*/)
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
			// 결과값이 존재하면 mysql에서 결과값을 얻어오는 함수
			MYSQL_RES* result = mysql_store_result(m_DBHandle);

			if (nullptr != result)
			{
				// 한 행에서 리턴되는 값을 얻어올수 있는 구조체
				MYSQL_ROW row;
				unsigned int fields = mysql_num_fields(result);

				// 여기 들어오면 
				// while을 돌려서 각 행에 해당하는 
				// 값들을 MYSQL_ROW row;에 담아서 볼수 있다.
				// 값이 없다면 
				while (row = mysql_fetch_row(result))
				{
					std::shared_ptr<RowDataType> NewData = std::make_shared<RowDataType>();
					std::vector<DBVar*>& Fields = NewData->GetDBVarData();
					_Vector.push_back(NewData);
					// 각 행을 가져오는 것.
					++m_affectedRow;
					for (unsigned int i = 0; i < fields; i++)
					{
						Fields[i]->Setting(row[i]);

						// 실제적으로 이곳에서 값의 변환이 일어나야 합니다.

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
					// 리턴이 없는 녀석들은 이것으로 처리가 된다.
				}
				else
				{
					// 뭔가 그냥 에러가 났다.
					break;
				}
			}

			QueryResult = mysql_next_result(m_DBHandle);

		} while (0 == QueryResult);

		// 이를 통해서 증가된 오토 인클리먼트(DB가 관리해주는 자동증가값) 얻어오기
		m_LastInsertId = mysql_insert_id(m_DBHandle);

		return true;
    }

    // 언제나 한 행의 데이터를 기준으로 삼아서 그것들을 가져오게하겠다.

};

#endif