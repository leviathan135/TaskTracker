#include "Json.h"


Json::Json() : m_jsonFilePath(NULL)
{

}

Json::Json(char* jsonFilePath)
{
	setJsonFilePath(jsonFilePath);
	//m_jsonFile(getJsonFilePath(), std::fstream::in | std::fstream::out);
}

EXEC_RESULT::EXEC_RESULT Json::parse(JsonData* jsonData)
{
	EXEC_RESULT::EXEC_RESULT result = EXEC_RESULT::FAILURE;
	if (getJsonFilePath() == NULL)
	{
		printError("jsonFilePath is not given!\n");
	}

	m_jsonFile.open((const char*)getJsonFilePath(), std::fstream::in | std::fstream::out | std::fstream::app);
	if (m_jsonFile.is_open())
	{
		std::cout << "Parsing " << getJsonFilePath() << " ... " << std::endl;
	}
	else
	{
		printError("Json File cannot open!!");
		return EXEC_RESULT::FAILURE;
	}

	//Check opening curly bracket
	result = checkCurlyBracket('{', m_jsonFile);

	if (result != EXEC_RESULT::SUCCESS)
	{
		printError("This is not a json file. Be sure read correct form of json file");
		return EXEC_RESULT::FAILURE;
	}

	//Okuma isini hallet. 
	std::string key;

	//while (1)
	{
		result = readKey(key, m_jsonFile);
		std::cout << "okunan key degeri : " << key << " ve result sonucu " << result << std::endl;
		jsonData->insertKey(key);
		result = readValue()

	}


	//Check close bracket
	//checkCurlyBracket('}', m_jsonFile);
	
	
	/*
	char word;
	int a = 0;
	while (m_jsonFile >> word)
	{
		std::cout << word << std::endl;
		std::cout << a <<std::endl;
		a++;
	}*/

	return result;
}

EXEC_RESULT::EXEC_RESULT Json::readKey(std::string& key, std::fstream& jsonFile)
{
	char c;
	jsonFile >> c;
	if (c != '"')
	{
		printError("DoubleQuotes can not be readed. Check json file format!");
		return EXEC_RESULT::FAILURE;
	}

	jsonFile >> c;
	while (c != '"')
	{
		key = key + c;
		jsonFile >> c;
	}
	//In last jsonFile>>c ending doublequotes readed. Lastly read semicolon.

	jsonFile >> c;
	if (c != ':')
	{
		printError("Semicolon is not readed. Check json file format!");
		return EXEC_RESULT::FAILURE;
	}
	return EXEC_RESULT::SUCCESS;
}

EXEC_RESULT::EXEC_RESULT Json::checkCurlyBracket(char curlyBracket, std::fstream& jsonFile)
{
	char c;
	jsonFile >> c;
	if (c == curlyBracket)
	{
		return EXEC_RESULT::SUCCESS;
	}   
	else
	{
		return EXEC_RESULT::FAILURE;
	}
}

void Json::openJsonFile()
{
	if (getJsonFilePath() == NULL)
	{
		printError("jsonFilePath is not given!\n");
	}

	//Yeni bir dosay yaratilacagi icin std::fstream::in arguman olarak verilemez, verilecekse de std::fstream::trunc eklenmeli.
	m_jsonFile.open((const char*)getJsonFilePath(), std::fstream::in|std::fstream::out |std::fstream::trunc);
	if (m_jsonFile.is_open())
	{
		m_jsonFile.write("{", 1);
	}
	else
	{
		//@TODO throw error akisi calisalacak. 
		//throw("Json Dosyasi acilamadi");
		std::cerr << "JsonFile is not opened" << std::endl;
		throw("Json file is not opened");
	}

}

void Json::closeJsonFile()
{
	//@TODO hata akisi ekelencek. dosya acik mi degil mi kontrol et gibi.
	if (m_jsonFile.is_open())
	{
		m_jsonFile.write("}", 1);
		m_jsonFile.close();
	}

}

EXEC_RESULT::EXEC_RESULT Json::writeJsonDataToJsonFile(JsonData* jsonData)
{
	//@TODO: test amacli sadece keyler yazildi. Daha sonrasýn key/value pairler yazýlacak.
	std::vector<std::string>::iterator it;
	std::vector<AbstractJsonDataType*>::iterator itr2 = jsonData->getValues().begin();
	int i = 0;

	for (it = jsonData->getKeys().begin(); it != jsonData->getKeys().end(); it++,i++)
	{
		m_jsonFile << "\"";
		m_jsonFile<<*it<<"\""<<":"; //Semicolondan sonra value yazilacak 
		(jsonData->getValues().at(i))->write(m_jsonFile);
		//*itr2.write();

		if (it != (jsonData->getKeys().end() - 1))
		{
			m_jsonFile << ",";
		}
	}

	return EXEC_RESULT::SUCCESS;

}

Json::~Json(){}


