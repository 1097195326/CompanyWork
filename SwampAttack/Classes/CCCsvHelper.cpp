#include "CCCsvHelper.h"
#include "ConfigManager.h"


using namespace std;


GCCsvHelper::GCCsvHelper(const std::string fileName)
	:m_seperator(",")
	,m_colLength(0)
{
    ConfigManager::getInstance()->addConfigData(fileName, this);
    openAndResolveFile(fileName);
}

GCCsvHelper::~GCCsvHelper()
{

}

#pragma region reselove the content begin...
string findTag(string & content)
{
    string::size_type index = content.find_first_of('[',0);
    string tag = content.substr(0,index);
    if (string::npos != index)
    {
        return tag;
    }
    return NULL;
}
string findType(string & content)
{
    string::size_type index = content.find_first_of('[',0);
    string::size_type lastIndex = content.find_last_of(']');
    if (string::npos != index && string::npos != lastIndex)
    {
        ++index;
        string type = content.substr(index,lastIndex - index);
        return type;
    }
    return NULL;
}
void rowSplit(std::vector<std::string> &rows, const std::string &content, const char &rowSeperator)
{
    std::string::size_type lastIndex = content.find_first_not_of(rowSeperator, 0);
    std::string::size_type    currentIndex = content.find_first_of(rowSeperator,lastIndex);
    
    while (std::string::npos != currentIndex || std::string::npos != lastIndex) {
        //        printf("hong xing rows :%s",content.substr(lastIndex, currentIndex - lastIndex).c_str());
        rows.push_back(content.substr(lastIndex, currentIndex - lastIndex));
        lastIndex = content.find_first_not_of(rowSeperator, currentIndex);
        currentIndex = content.find_first_of(rowSeperator, lastIndex);
    }
}

Json::Value jsonDataSplit(const std::string &content,char seperator, std::vector<std::string> tags);
void test(const std::string &content,char seperator)
{
    
}
Json::Value jsonDataSplit(const std::string & content, char seperator[], char sepe, std::vector<std::string> tags)
{
    Json::Value jsonObject;
    
    int i = 0;
    std::vector<std::string> data;
    
    while(i < 2)
    {
        char sep = seperator[i];
        
        if (i == 0)
        {
            rowSplit(data,content,sep);
        }else if(i == 1)
        {
            for (int j = 0; j < data.size(); ++j)
            {
                Json::Value obj;
                
                std::vector<std::string> data2;
                rowSplit(data2,data[j],sep);
                for (int k = 0; k < data2.size(); ++k)
                {
                    Json::Value o = jsonDataSplit(data2[k],sepe,tags);
                    obj.append(o);
                }
                jsonObject.append(obj);
            }
        }
        ++i;
    }
    
    return jsonObject;
}

Json::Value jsonDataSplit(const std::string &content,char seperator, std::vector<std::string> tags)
{
    Json::Value jsonObject;
    
    std::string::size_type lastIndex = content.find_first_not_of(seperator, 0);
    std::string::size_type    currentIndex = content.find_first_of(seperator,lastIndex);
    
    int i = 0;
    while (std::string::npos != currentIndex || std::string::npos != lastIndex)
    {
        i = i % 2;
        
        jsonObject[tags[i].c_str()] = content.substr(lastIndex, currentIndex - lastIndex).c_str();
        lastIndex = content.find_first_not_of(seperator, currentIndex);
        currentIndex = content.find_first_of(seperator, lastIndex);
        i++;
    }
    return jsonObject;
}
Json::Value jsonDataSplit(const std::string &content,char seperator)
{
    Json::Value jsonObject;
    
    std::string::size_type lastIndex = content.find_first_not_of(seperator, 0);
    std::string::size_type    currentIndex = content.find_first_of(seperator,lastIndex);
    while (std::string::npos != currentIndex || std::string::npos != lastIndex)
    {
        jsonObject.append(content.substr(lastIndex, currentIndex - lastIndex).c_str());
        lastIndex = content.find_first_not_of(seperator, currentIndex);
        currentIndex = content.find_first_of(seperator, lastIndex);
    }
    return jsonObject;
}
bool GCCsvHelper::openAndResolveFile(const std::string fileName)
{
    char  configPath[100] = "config/";
    
    std::string pathKey = FileUtils::getInstance()->fullPathForFilename(strcat(configPath, fileName.c_str()));
    std::string pBuffer = FileUtils::getInstance()->getStringFromFile(pathKey.c_str());
    
//    log("%s",pBuffer.c_str());
    std::vector<std::vector<std::string> >  data;
	std::vector<std::string> line;
	rowSplit(line, pBuffer, '\n');
	for (unsigned int i = 0; i < line.size(); ++i)
    {
		std::vector<std::string> fieldVector;
		fieldSplit(fieldVector, line[i]);
		data.push_back(fieldVector);
		m_colLength = std::max(m_colLength, (int)fieldVector.size());
	}
    createJsonData(data);

	return true;
}
Json::Value GCCsvHelper::getJsonData()
{
    return root;
}
void GCCsvHelper::createJsonData(std::vector<std::vector<std::string> > & data)
{
    //----------生成 json
    Json::FastWriter writer;
    
    std::vector<std::string> headLine = data[1];
    for (int i = 2; i < data.size(); ++i) {
        std::vector<std::string> line = data[i];
        Json::Value lineArray;
        for (int i = 0; i < headLine.size(); ++i)
        {
            string head = headLine[i];
            string str = line[i];
            
            if ("" != head)
            {
                string tag = findTag(head);
                string type = findType(head);
                
                if (string::npos != type.find("vector"))
                {
                    Json::Value jsonObject;
                    
                    std::vector<std::string> subTagStr;
                    rowSplit(subTagStr, type, ';');
                    
                    std::vector<std::string> tags;
                    if (subTagStr.size() == 1)
                    {
                        char seperator = ';';
                        jsonObject[tag.c_str()] = jsonDataSplit(str,seperator);
                    }else
                    {
                        for (int i = 1; i < subTagStr.size(); ++i)
                        {
                            tags.push_back(findTag(subTagStr[i]));
//                            log("%s",findTag(subTagStr[i]).c_str());
                        }
                        char seperator[] = {'|',';'};
                        jsonObject[tag.c_str()] = jsonDataSplit(str,seperator,':',tags);
                    }
                    
                    lineArray.append(jsonObject);
                }else
                {
                    Json::Value object;
                    object[tag.c_str()] = str.c_str();
                    lineArray.append(object);
                }
            }
        }
        Json::Value lineObject;
        lineObject[line[0].c_str()] = lineArray;
        root.append(lineObject);
    }
    std::string json_file = writer.write(root);
    log("%s",json_file.c_str());
}

void GCCsvHelper::rowSplit(std::vector<std::string> &rows, const std::string &content, const char &rowSeperator)
{
	std::string::size_type lastIndex = content.find_first_not_of(rowSeperator, 0);
	std::string::size_type    currentIndex = content.find_first_of(rowSeperator,lastIndex);

	while (std::string::npos != currentIndex || std::string::npos != lastIndex) {
//        printf("hong xing rows :%s",content.substr(lastIndex, currentIndex - lastIndex).c_str());
		rows.push_back(content.substr(lastIndex, currentIndex - lastIndex));
		lastIndex = content.find_first_not_of(rowSeperator, currentIndex);
		currentIndex = content.find_first_of(rowSeperator, lastIndex);
	}
}

void GCCsvHelper::fieldSplit(std::vector<std::string> &fields, std::string line)
{
	if (line[line.length() - 1] == '\r') {
		line = line.substr(0, line.length() - 1);
	}
	std::string field;
	unsigned int i = 0, j = 0;
	while (j < line.length()) {
		if (line[i] == '"') {
			//有引号
			j = getFieldWithQuoted(line, field, i);
            i = j + 2;
		} else {
			j = getFieldNoQuoted(line, field, i);
            i = j + 1;
		}
		fields.push_back(field);
//		i = j + 1; //解析下一个field， ＋1为了跳过当前的分隔符
	}
}

int GCCsvHelper::getFieldWithQuoted(const std::string &line, std::string &field, int i)
{
	unsigned int j = 0;
	field = std::string();
	if (line[i] != '"') {
		//不是引号起始，有问题
		CCLOGERROR("start char is not quote when call %s", __FUNCTION__);
		return -1;
	}

	for (j = i + 1; j < line.length() - 1; ++j) {
		if (line[j] != '"') {
			//当前char不为引号，则是field内容(包括逗号)
			field += line[j];
		} else {
			//遇到field结束时的引号，可以返回
			return j;
			break;
		}
	}

	if (j == line.length()) {
		//没有找到成对的结束引号
		CCLOGERROR("resoleve the line error: no pair quote, line:%s, field:%s, start index:%d", line.c_str(), field.c_str(), i);
	}

	return j;
}

int GCCsvHelper::getFieldNoQuoted(const std::string &line, std::string &field, int index)
{
	unsigned int j = 0;
	//找到下一个分隔符位置
	j = (unsigned int)line.find_first_of(m_seperator, index);
	if (j > (unsigned int)line.length()) {
		j = (unsigned int)line.length();
	}

	field = std::string(line, index, j - index);

	return j;
}