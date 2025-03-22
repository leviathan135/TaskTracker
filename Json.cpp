#include "Json.h"


Json::Json() : m_jsonFilePath(NULL), isJsonFileReadCompleted(false)
{

}

Json::Json(char* jsonFilePath): isJsonFileReadCompleted(false)
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
		return EXEC_RESULT::FAILURE;
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
	result = checkCurlyBracket('{');

	if (result != EXEC_RESULT::SUCCESS)
	{
		printError("This is not a json file. Be sure read correct form of json file");
		return EXEC_RESULT::FAILURE;
	}

	//Okuma isini hallet. 
	std::string key;
	AbstractJsonDataType* value;

	while (!isJsonFileReadCompleted)
	{
		result = readKey(key);
		jsonData->insertKey(key);
		//clear key 
		key.clear();
		value =  readValue(jsonData);
		jsonData->insertValue(value);
	}
	m_jsonFile.close();
	//json file parsed and then closed.
	return result;
}

AbstractJsonDataType* Json::readValue(JsonData* jsonData)
{
	AbstractJsonDataType* p_jsonValue;
	std::string valueAsString;
	char c;
	m_jsonFile >> c;
	while (c != ',' && c != '}') //Either value read ended and there is other key and value, or json file ended with number.
	{
		valueAsString = valueAsString + c;
			
		if (valueAsString[0] == '[')
		{
			while (c != ']')
			{
				m_jsonFile >> c;
				valueAsString = valueAsString + c;
			}
		}
		m_jsonFile >> c;
	}

	if (valueAsString[0] == '{')
	{
		valueAsString = valueAsString + c; //If end of file not reached put } to file to check json object read or not.
		m_jsonFile >> c;
		if (c == '}') //json file read finished with last object as an json object.
		{
			isJsonFileReadCompleted = true;
		}
		else //that means next character is ','
		{
			isJsonFileReadCompleted = false;
		}
	}
	else if(c == '}') //Closing curly bracket readed.
	{
		isJsonFileReadCompleted = true;
	}


	std::cout << "valueasString degerii: " << valueAsString << std::endl;
	if (valueAsString[0] == '"') //This is a jsonString. read string
	{
		p_jsonValue = new JsonStringDataType();
		p_jsonValue->read(valueAsString);
		
	}
	else if (valueAsString[0] == '[') //This is a json array. read array
	{
		p_jsonValue = new JsonArrayDataType();
		
		p_jsonValue->read(valueAsString);
		std::cout << "valueasArray degerii: " << valueAsString << std::endl;
		// Yapilacak..
	}/*
	else if (valueAsString[0] == '{') //This is a json object. read json object as stringfyed.
	{
		//@TODO implement later.
	}
	else if (valueAsString[0] == ',' || valueAsString[0] == '}') //This is null. Either next key will come or json object read completed.
	{
		//@TODO implement later.
	}
	else if (valueAsString[0] == 't' || valueAsString[0] =='f') //This is a json boolean.
	{
		if (valueAsString[0] == 't')
		{
			//@TODO implement json boolean as true
		}
		else {
			//@TODO implement json boolean as false
		}
	}*/
	else
	{
		//Json number int or double.
		p_jsonValue = new JsonNumberDataType();
		p_jsonValue->read(valueAsString);
		
	}

	return p_jsonValue;
	
}

EXEC_RESULT::EXEC_RESULT Json::readKey(std::string& key)
{
	char c;
	m_jsonFile >> c;
	if (c != '"')
	{
		printError("DoubleQuotes can not be readed. Check json file format!");
		return EXEC_RESULT::FAILURE;
	}

	m_jsonFile >> c;
	while (c != '"')
	{
		key = key + c;
		m_jsonFile >> c;
	}
	//In last jsonFile>>c ending doublequotes readed. Lastly read semicolon.

	m_jsonFile >> c;
	if (c != ':')
	{
		printError("Semicolon is not readed. Check json file format!");
		return EXEC_RESULT::FAILURE;
	}
	return EXEC_RESULT::SUCCESS;
}

EXEC_RESULT::EXEC_RESULT Json::checkCurlyBracket(char curlyBracket)
{
	char c;
	m_jsonFile >> c;
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


