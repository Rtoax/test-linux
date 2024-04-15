#include <iostream>

using namespace std;

class bus {
public:
	int getNo(void);
	void setNo(int no);

private:
	int no;
};

int bus::getNo(void)
{
	return this->no;
}

void bus::setNo(int no)
{
	this->no = no;
}

int main(void)
{
	bus b;

	b.setNo(123);
	cout << b.getNo() << endl;
	cout << "rongtao" << endl;

	return 0;
}
