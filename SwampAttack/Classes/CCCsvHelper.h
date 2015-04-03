#ifndef __Cell__CCCsvHelper__
#define __Cell__CCCsvHelper__

#include <iostream>
#include "cocos2d.h"
#include <vector>
#include "json/json.h"

USING_NS_CC;

class GCCsvHelper
{
public:
	GCCsvHelper(const std::string fileName);
	~GCCsvHelper();

    Json::Value getJsonData();
	
private:
	const   std::string m_seperator;
    Json::Value root;
	//cols length
	int     m_colLength;
    int     m_rowLength;
    
    bool    openAndResolveFile(const std::string fileName);
    inline  int     getColLength() { return m_colLength; }
    inline  int     getRowLength() {    return m_rowLength; }
    
    void    createJsonData(std::vector<std::vector<std::string> > & data);
	void    rowSplit(std::vector<std::string> &rows, const std::string &content, const char &rowSeperator);
	void    fieldSplit(std::vector<std::string> &fields, std::string line);
	//获取带引号的字段
	int     getFieldWithQuoted(const std::string &line, std::string& field, int index);
	//获取无引号的字段
	int     getFieldNoQuoted(const std::string &line, std::string &field, int index);
};

#endif /* defined(__Cell__CCCsvHelper__) */