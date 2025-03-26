
#include "AbstractJsonDataType.h"
#include <vector>
#include "JsonDataTypes.h"

//@TODO: test amacli kaldiralacak.
#include <iostream>

class JsonArrayDataType : public AbstractJsonDataType
{
public:
	JsonArrayDataType();
	JsonArrayDataType(JSON_DATA_TYPE jsonArrayDataType);
	~JsonArrayDataType();

	void write(std::fstream& jsonFile);
	void read(std::string arrayData);
	std::string getDataString();
	void setDataString(std::string arrayData);
	void parseArray(std::string arrayData);
	void obtainArrayDataType(std::string arrayData);
	void parseNumberData(std::string numberArray);

	void insertArrayValue(AbstractJsonDataType* jsonDataValue);
	void removeArrayValue(std::string value);

	JSON_DATA_TYPE getDataType()
	{
		return m_arrayDataType;
	}

	void setDataType(JSON_DATA_TYPE dataType)
	{
		m_arrayDataType = dataType;
	}

	std::vector<AbstractJsonDataType*>& getJsonArray()
	{
		return m_jsonArray;
	}

	void setJsonArray(std::vector<AbstractJsonDataType*> jsonArray)
	{
		m_jsonArray = jsonArray;
	}

private:
	std::vector<AbstractJsonDataType* > m_jsonArray;
	JSON_DATA_TYPE m_arrayDataType = NOT_SPECIFIED;
	std::string m_stringyfedJsonArray;

};
