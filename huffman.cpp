#include<iostream>
#include<string>
#include<cstring>

struct HuffmanNode
{
	int weight;
	char value;
	std::string code;
	int lIndex,rIndex,parentIndex;
};

class HuffmanCode
{
	public:
	explicit HuffmanCode(const std::string &str); //构造函数，在构造函数中实现编码全过程
	~HuffmanCode(); //析构函数，释放分配的内存
	void setMin(int& lMinIndex,int& rMinIndex,int parentIndex);
       	void merge(int lMinIndex,int rMinIndex,int parentIndex);
	void coding();
	void decode(const std::string& str);
	
	private:
	int leafNumber; //存储不同字符的个数 也就是哈夫曼树叶子节点个数
	HuffmanNode* huffmanTree;	
};

HuffmanCode::HuffmanCode(const std:string& str)
{
	huffmanTree = new HuffmanNode[256];
	leafNumber = 0;

	int length = str.size();
	int ascii[256];
	memset(ascii,0,sizeof(ascii));

	for(int i = 0;i < (2 * length - 1);i++)
	{
		huffmanTree[i].parentIndex = huffmanTree[i].rIndex = huffmanTree[i].lIndex = -1;
		huffmanTree[i].code = "";
	}

	//记录每个字符的权重
	for(int i = 0;i < length;i++)
	{
		ascii[str[i]]++;
	}

	//记录所有叶子节点的值和权重
	for(int i = 0;i < 256;i++)
	{
		if(ascii[i] != 0)
		{
			huffmanTree[leafNumber].value = (char)i; //值
			huffmanTree[leafNumber].weight = ascii[i]; //权重
			++leafNumber;
		}
	}

	int lMinIndex,rMinIndex;
	for(int parentIndex = leafNumber;parentIndex < (2 * leafNumber - 1);++parentIndex)
	{
		setMin(lMinIndex,rMinIndex,parentIndex);
		merge(lMinIndex,rMinINdex,parentIndex);
	}
}

HuffmanCode::~HuffmanCode()
{
	delete []huffmanTree;
}

void HuffmanCode::setMin(int& lMinIndex,int& rMinIndex,int parentIndex)
{
	double weight = 0;
	for(int i = 0;i < parentIndex;i++)
	{
		if(huffmanTree[i].parentIndex != -1) //已经被选过的节点
			continue;
		if(weight == 0)
		{
			weight = huffmanTree[i].weight;
			lMinIndex = i;
		}
		else if(huffmanTree[i].weight < weight)
		{
			weight = huffmanTree[i].weight;
			lMinIndex = i;
		}
	}

	weight = 0;

	for(int i = 0;i < parentIndex;i++) //和上面操作一致
	{
		if(huffmanTree[i].parentIndex != -1)
			continue;
		if(weight == 0)
		{
			weight = huffmanTree[i].weight;
			rMinIndex = i;
		}
		else if(huffmanTree[i].weight < weight)
		{
			weight = huffmanTree[i].weight;
			rMinIndex = i;
		}
	}
}

void HuffmanCode::merge(int lMinIndex,int rMinIndex,int parentIndex)
{
	huffmanTree[lMinIndex].parentIndex = huffmanTree[rMinIndex].parentIndex = parentIndex;
	huffmanTree[parentIndex].lIndex = lMinIndex;
	huffmanTree[parentIndex].rIndex = rMinIndex;
	huffmanTree[parentIndex].weight = huffmanTree[lMinIndex].weight + huffmanTree[rMinIndex].weight;
}

void HuffmanCode::coding()
{
	std::string code;
	int parentIndex,tempIndex;
	//从叶子节点出发
	for(int i = 0;i < leafNumber;i++)
	{
		code = "";
		tempIndex = i;

		while(huffmanTree[tempIndex].parentIndex != -1)
		{
			parentIndex = huffmanTree[tempIndex].parentIndex;
			if(tempIndex == huffmanTree[parentIndex].lIndex)
				code += "0";
			else
				code += "1";
			tempIndex = parentIndex;
		}

		//把编码倒过来
		for(int j = (int)code.size() - 1;j >= 0;j--)
		{
			huffmanTree[i].code += code[j];
		}

		std::cout << "字符：" << huffmanTree[i].value << "的编码为：" << huffmanTree[i].code << std::endl;

	}
}

void HuffmanCode::decode(const std::string &str)
{
	std::string decode,tempCode;
	decode = tempCode = "";
	int length = (int)str.size();
	
	int i,j;
	for(i = 0;i < length;i++)
	{
		tempCode += str[i];
		for(j = 0;j < leafNumber;j++)
		{
			if(huffmanTree[j].code == tempCode)
			{
				decode += huffmanTree[j].value;
				tempCode = "";
				break;
			}
		}

		if(i == length - 1 && j == leafNumber)
		{
			std:: cout << "decode error"  << std:endl;
			return;
		}
	}
	std::cout << decode << std::endl;
}

int main()
{	
	std::string str;
	std::cout << "please input string to start coding:" << std::endl;
	std::cin >> str;
	HuffmanCode huffman(str);
	
	std::cout << "the situation for the code of string are as followed:" << std::endl;
	huffman.coding();
	std::cout << std::endl;

	std::cout << "please input binary code decode to string:" << std::endl;
	std::cin >> str;
	std::cout << "decode are as followed:" << endl;
	huffman.decode(str);
	
	return 0;
}


