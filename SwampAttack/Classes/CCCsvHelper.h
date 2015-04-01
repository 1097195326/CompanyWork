#ifndef __Cell__CCCsvHelper__
#define __Cell__CCCsvHelper__

#include <iostream>
#include "cocos2d.h"
#include <vector>

USING_NS_CC;

class GCCsvHelper
{
public:
	GCCsvHelper();
	~GCCsvHelper();

	bool    openAndResolveFile(const char *fileName);

	const   char    *getData(unsigned int rowIndex, unsigned int colIndex);

	inline  int     getColLength() { return m_colLength; }
    inline  int     getRowLength() {    return (int)data.size(); }

private:
	const   std::string m_seperator;
	std::vector<std::vector<std::string> >  data;

	//cols length
	int     m_colLength;

	void    rowSplit(std::vector<std::string> &rows, const std::string &content, const char &rowSeperator);
	void    fieldSplit(std::vector<std::string> &fields, std::string line);

	//获取带引号的字段
	int     getFieldWithQuoted(const std::string &line, std::string& field, int index);

	//获取无引号的字段
	int     getFieldNoQuoted(const std::string &line, std::string &field, int index);
};

#endif /* defined(__Cell__CCCsvHelper__) */