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
	// c형식인데.

	// 기본적인 db핸들을 만들어서 접속등의 명령을 수행할수 있게 해준다.
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

	// c 커넥터를 사용해서 c++ 커넥터를 사용하게 되는데.
	// c라이브러리와 c++라이브러리의 차이는 뭘까요?
	// c++형식은 객체지향
	// c형식은 절차지향
	// 객체지향의 대표적인 요소가.

	//MYSQLCPPCONNECT NewCon;
	//NewCon.connect()

	if (0 != mysql_options(m_DBHandle, MYSQL_SET_CHARSET_NAME, "utf8"))
	{
		GameEngineDebug::AssertMsg("if (0 != mysql_options(m_DBHandle, MYSQL_SET_CHARSET_NAME, utf8))");
		return false;
	}


	// CLIENT_MULTI_RESULTS 요걸 넣어주지 않으면 
	// 커넥터를 하나만 연결하고 사용하고 결과 값을 받을때
	// 다수의 쓰레드에서 처리가 안됩니다.
	// 한번에 다수의 db처리 결과값을 받기 위해서 사용하는 옵션
	MYSQL* MySqlConHandle = mysql_real_connect(m_DBHandle, _ip, _Id, _Password, _SchemaName, _Port, nullptr, CLIENT_MULTI_RESULTS);

	if (MySqlConHandle != m_DBHandle)
	{
		const char* Ptr = mysql_error(m_DBHandle);
		GameEngineDebug::AssertMsg("if (0 != mysql_options(m_DBHandle, MYSQL_SET_CHARSET_NAME, utf8))");
		return false;
	}

	bool reconnect = true;

	// db서버를 따로 두는 경우가 많습니다.
	// 머신 따로두고 db서버 운영한단 말이에요.
	// 이 옵션을 켜놓으면 mysql_ping 함수가
	// 리커넥트도 동시에 처리해주는 함수가 됩니다.
	if (0 != mysql_options(m_DBHandle, MYSQL_OPT_RECONNECT, &reconnect))
	{
		// 무슨 에러가 났는지 보여줍니다
		const char* Ptr = mysql_error(m_DBHandle);
		GameEngineDebug::AssertMsg(Ptr);
		return false;
	}

	return true;
}

bool DBConnecter::Ping(unsigned int _Count)
{
	// 핑은 실제 거의 모든 컴퓨터 환경에서 지원해주는 명령어가 있는데
	// 일반적으로 이 함수는 db가 살아있는지만 확인하는 함수가 되는데.

	for (size_t i = 0; i < _Count; i++)
	{
		if (0 != mysql_ping(m_DBHandle))
		{
			// 
		}
		else 
		{
			// 성공해서 연결이 복구됐으니 나가면 됩니다.
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
		// 결과값이 존재하면 mysql에서 결과값을 얻어오는 함수
		MYSQL_RES* result = mysql_store_result(m_DBHandle);

		if (nullptr != result)
		{
			// 한 행에서 리턴되는 값을 얻어올수 있는 구조체
			MYSQL_ROW row;
			unsigned int fields = mysql_num_fields(result);

			// while을 돌려서 각 열에 해당하는 
			// 값들을 MYSQL_ROW row;에 담아서 볼수 있다.
			// 값이 없다면 
			while (row = mysql_fetch_row(result))
			{
				++m_affectedRow;
				for (unsigned int i = 0; i < fields; i++)
				{
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

// member Func
#endif

