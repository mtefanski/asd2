#include <string>
#include <iostream>

class tablica
{
private:

	long key;
	std::string value;
	//bool flag;
	char flag;


public:

	tablica()
		:
		key(0),
		value(" "),
		flag('E')
	{
	}

	tablica(const tablica & copy)
		:
		key(copy.key),
		value(copy.value),
		flag(copy.flag)
	{
	}

	tablica operator=(const tablica& copy)
	{
		if (this == &copy)
			return *this;
		else
		{
			key = copy.key;
			value = copy.key;
			flag = copy.flag;
			return *this;
		}
	}

	void setKey(long key_)
	{
		key = key_;
	}

	void setValue(std::string value_)
	{
		value = value_;
	}

	void setFlag(char flag_)
	{
		flag = flag_;
	}

	long getKey()
	{
		return key;
	}

	std::string getValue()
	{
		return value;
	}

	char getFlag()
	{
		return flag;
	}

	tablica getTablica()
	{
		std::cout << key << " " << value << " " << flag << std::endl;
		return *this;
	}

};

class HT
{
private:
	tablica * tab;
	int size;
public:
	HT()
		:
		size(0)
	{
	}

	HT(const HT & copy)
		:
		size(copy.size)
	{
		tab = new tablica[size];

		for (int i = 0; i < size; i++)
		{
			tab[i].setKey(copy.tab[i].getKey());
			tab[i].setValue(copy.tab[i].getValue());
			tab[i].setFlag(copy.tab[i].getFlag());
		};
	}

	HT operator=(const HT& copy)
	{
		if (this == &copy)
			return *this;
		else
		{
			size = copy.size;

			tab = new tablica[size];

			for (int i = 0; i < size; i++)
			{
				tab[i].setKey(copy.tab[i].getKey());
				tab[i].setValue(copy.tab[i].getValue());
				tab[i].setFlag(copy.tab[i].getFlag());
			};

			return *this;
		}
	}

	~HT()
	{
		delete[] tab;
	}

	void Size(int size_)
	{
		if (size != size_)
		{

			size = size_;
			tab = new tablica[size];
			for (int i = 0; i < size; i++)
			{
				tab[i].setKey(0);
				tab[i].setValue(" ");
				tab[i].setFlag('E');
			};
		}
	}

	void Add(long key_, std::string value_)
	{
		int index = hash(key_);
		bool flag = false;

		do {

			if (tab[index].getValue() == " ")
			{
				tab[index].setKey(key_);
				tab[index].setValue(value_);
				tab[index].setFlag('F');
				flag = true;
			}
			else
			{
				tab[index].setFlag('C');

				index++;

				if (index == size)
					index = 0;
			}

		} while (flag != true);
	}

	void Print()
	{

		for (int i = 0; i < size; i++)
		{
			/*if (tab[i].getValue() != " ")
			{*/
				std::cout << i << " ";
				tab[i].getTablica();
			/*}*/
		}
		std::cout << std::endl;
	}

	void Delete(long key_)
	{
		int index = hash(key_);
		int deleted = 0;
		bool flag = false;

		do {
			if (tab[index].getKey() == key_ && tab[index].getValue() != " " )
			{
				tab[index].setKey(0);
				tab[index].setValue(" ");
				tab[index].setFlag('E');
				deleted = index;
				flag = true;
			}

			else if (tab[index].getFlag() == 'C')
			{
				index++;
				if (index == size)
					index = 0;
			}

		} while (flag != true);

		//wypelnianie wolnego miejsca
		//int replaced;
		index = deleted+1;
		flag = false;
		do {
			if (hash(tab[index].getKey()) == deleted)
			{
				Add(tab[index].getKey(), tab[index].getValue());
				//replaced = index;
				tab[index].setKey(0);
				tab[index].setValue(" ");
				flag = true;

			}
			else if (tab[index].getFlag() == 'C' || tab[index].getFlag() == 'F')
			{
				index++;
				if (index == size)
					index = 0;
			}

		} while (flag != true);
		
		//ustawianie flag od nowa

		index = deleted + 1;
		flag = false;
		/*std::cout << replaced << std::endl;

		for (replaced; replaced >= deleted; replaced--)
		{
			std::cout << replaced;
		}
		std::cout << std::endl;*/

		do {
		if (tab[index].getFlag() == 'C' && tab[index + 1].getFlag() == 'F' && tab[index + 1].getValue() == " ")
		{
			tab[index].setFlag('F');
			tab[index + 1].setFlag('E');
			flag = true;
			//break;
		}
		else if (tab[index].getFlag() == 'F' && tab[index].getValue() == " ")
		{
			tab[index].setFlag('E');
			flag = true;
			//break;
		}
		/*else if (tab[index].getFlag() == 'C' && tab[index + 1].getFlag() == 'C')
		{
			index++;
			if (index == size)
				index = 0;
		}*/
		} while (flag == false);

	}

	int hash(long key_)
	{
		return key_ % size;
	}
};

int main()
{

	HT ht_;
	ht_.Size(10);
	ht_.Add(13, "ala");
	//ht_.Print();
	ht_.Add(24, "ola");
	//ht_.Add(25, "jola");
	ht_.Add(23, "ela");
	//ht_.Print();
	//ht_.Delete(13);
	//ht_.Print();
	//ht_.Add(19, "aaa");
	//ht_.Add(29, "bbb");
	ht_.Print();
	ht_.Delete(13);
	ht_.Print();


	system("pause");
	return 0;
}