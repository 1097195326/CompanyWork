#include "CCCsvHelper.h"

GCCsvHelper::GCCsvHelper()
	:m_seperator(",")
	,m_colLength(0)
{

}

GCCsvHelper::~GCCsvHelper()
{

}

#pragma region reselove the content begin...

bool GCCsvHelper::openAndResolveFile(const char *fileName)
{
    char  configPath[100] = "config/";
    
    std::string pathKey = FileUtils::getInstance()->fullPathForFilename(strcat(configPath, fileName));
//    printf("hong xing file path :%s \n",pathKey.c_str());
    std::string pBuffer = FileUtils::getInstance()->getStringFromFile(pathKey.c_str());
    
    
    printf("hong xing csv :\n%s",pBuffer.c_str());
    
	std::vector<std::string> line;
	rowSplit(line, pBuffer, '\n');
	for (unsigned int i = 0; i < line.size(); ++i) {
		std::vector<std::string> fieldVector;
		fieldSplit(fieldVector, line[i]);
		data.push_back(fieldVector);
		m_colLength = std::max(m_colLength, (int)fieldVector.size());
	}

	return true;
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
		} else {
			j = getFieldNoQuoted(line, field, i);
		}

		fields.push_back(field);
		i = j + 1; //解析下一个field， ＋1为了跳过当前的分隔符
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

#pragma region end.

///////search data
const char *GCCsvHelper::getData(unsigned int rowIndex, unsigned int colIndex)
{
	if (rowIndex >= getRowLength() || colIndex >= getColLength()) {
		return "";
	}

	if (colIndex >= data[rowIndex].size()) {
		return "";
	}

	return data[rowIndex][colIndex].c_str();
}