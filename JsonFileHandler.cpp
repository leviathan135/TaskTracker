#include "JsonFileHandler.h"

JsonFileHandler::JsonFileHandler() : m_jsonFilePath(NULL) {

}

JsonFileHandler::~JsonFileHandler() {};

EXEC_RESULT::EXEC_RESULT JsonFileHandler::updateTaskJson(char* newTask)
{
	EXEC_RESULT::EXEC_RESULT result = EXEC_RESULT::FAILURE;

	//Check is json file exist with given id or not?
	if (!isFileExists(getJsonFilePath()))
	{
		printError("The json file you want to update does not exist. Do you want to create new one with given description?\n");
		//@TODO: Burada cevaba gore kullaniciyi yes/no cevabindan sonra add fonksiyonu ile yönlendir. Ýleri seviye.
		return result;
	}

	//If json file exists, open json file.
	Json jsonFile;
	jsonFile.setJsonFilePath(getJsonFilePath());

	//Create jsonData to store  key and values.
	JsonData jsonData;

	jsonFile.parse(&jsonData);
		


	//TODO List
	// 1) Path hazir olarak verildi. ID kullanici tarafindan verildi zaten json icerisinde tutuluyor.
	// Task cpp içerisinde path bu class içerisine zaten atanmýþ durumda her method içerisinde path ayarlanýyor bu yüzden daha üst bir seviyede ya da
	// class objesi olarak jsonfile oluþturulabilir method içerisinde tekrarlý þekilde oluþturuluyor. 
	// 2) Once dosyayý oku 
	// 3) Dosya icerisinde okunan her bir keyi ve degerini tut. Buna gore pair tarzi bir yapi oluþturulabilinir. Bu islem aslinda json.parse()
	// 4) Daha sonra ilgili key/value gincelle. Bu durumda taskdescription ve updated-at güncellenecek.
	// 5) Bu deðerler güncellendikten sonra json.stringfy()
	// 6) parse ve stringfy daha fazla ilerlenmeden diger methodlar icerisinde de caðýrýlýp genel kütüphane oluþturulabilinir. 
	//

	return result;
}

EXEC_RESULT::EXEC_RESULT JsonFileHandler::createNewTaskJson(char* newTask)
{
	uint32_t result = 0;

	Json jsonFile;
	jsonFile.setJsonFilePath(getJsonFilePath());
	jsonFile.openJsonFile();

	//Create JsonData
	JsonData jsonData;
	jsonData.insertKeyVector(getTaskKeys());
	//Add each value of keys
	// First add task id, task description and status
	int id = std::rand();
	result += addJsonNumber(jsonData, id);
	result += addJsonString(jsonData, std::string(newTask));
	result += addJsonString(jsonData, "todo");

	std::string dateTime = getCurrentDateTime();

	//Second, add created and updated time 
	result += addJsonString(jsonData, dateTime);
	result += addJsonString(jsonData, dateTime);

	result += jsonFile.writeJsonDataToJsonFile(&jsonData);//This is actually json.strignfy function.
	//TODO write task information into the json file


	jsonFile.closeJsonFile();

	if (result == 0)
	{
		std::cout << "Task added successfully (ID:" << id << ")";
		return EXEC_RESULT::SUCCESS;
	}
	else {
		return EXEC_RESULT::FAILURE;
	}
}

EXEC_RESULT::EXEC_RESULT JsonFileHandler::addJsonString(JsonData& jsonData, std::string newTask)
{
	AbstractJsonDataType* jsonStringDataType = new JsonStringDataType(newTask);
	jsonData.insertValue(jsonStringDataType);
	return EXEC_RESULT::SUCCESS;
}

EXEC_RESULT::EXEC_RESULT JsonFileHandler::addJsonNumber(JsonData& jsonData, int id)
{
	//@TODO: buradaki id degeri configden okunacak. Daha sonra ayarla.
	AbstractJsonDataType* jsonNumberDataType = new JsonNumberDataType(id);
	jsonData.insertValue(jsonNumberDataType);
	return EXEC_RESULT::SUCCESS;
}



