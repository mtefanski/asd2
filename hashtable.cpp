#include <string>
#include <iostream>

class tablica
{
private:

	long key;
	std::string value;
	char flag;

public:

	tablica()
		:
		key(0),
		value(" "),
		flag('E')
	{
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
		std::cout << key << " " << value << std::endl;
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
			if (tab[i].getValue() != " ")
			{
				std::cout << i << " ";
				tab[i].getTablica();
			}
		}
		std::cout << std::endl;
	}

	void Delete(long key_)
	{
		int index = hash(key_);
		int deleted = 0;

		//_______________usuwanie elementu o podanym kluczu_____________
		while (tab[index].getFlag() != 'E')
		{
			if (tab[index].getKey() == key_ && tab[index].getValue() != " ")
			{
				tab[index].setKey(0);
				tab[index].setValue(" ");
				deleted = index;
				break;
			}
			else
			{
				index++;
				if (index == size)
					index = 0;
			}
		}
		//_________________________________________________________________

		//______________________ile elementow o zadanym hashu jest w lancuchu?
		int elementow = 0;
		int ostatni = 0;

		while (tab[index].getFlag() != 'E')
		{
			if (hash(tab[index].getKey()) == hash(key_) && tab[index].getValue() != " ")
			{
				elementow++;
				ostatni = index;
			}

			if (tab[index].getFlag() == 'F')
				break;

			index++;
			if (index == size)
				index = 0;
		}
		//____________________________________________________________________

		//____________________________________________________________________
		if (elementow == 1)
		{
			Add(tab[ostatni].getKey(), tab[ostatni].getValue());
			tab[ostatni].setKey(0);
			tab[ostatni].setValue(" ");
		}
		else if (elementow > 1)
		{
			Add(tab[ostatni].getKey(), tab[ostatni].getValue());
			tab[deleted].setFlag('C');
			tab[ostatni].setKey(0);
			tab[ostatni].setValue(" ");
		}
		//_______________________________________________________________________
		ustawFlagi(ostatni);
	}

	void ustawFlagi(int index_)
	{
		if (tab[index_].getFlag() == 'F')
		{
			tab[index_].setFlag('E');
			tab[index_ - 1].setFlag('F');
		}
		else if (tab[index_].getFlag() == 'C')
		{

			index_++;
			while (tab[index_].getFlag() != 'E')
			{
				if (hash(tab[index_].getKey()) != index_)
				{
					Add(tab[index_].getKey(), tab[index_].getValue());
					tab[index_].setKey(0);
					tab[index_].setValue(" ");
					ustawFlagi(index_);
				}

				if (tab[index_].getFlag() == 'F')
					break;

				index_++;
				if (index_ == size)
					index_ = 0;
			}
		}
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
	ht_.Print();
	ht_.Add(23, "ola");
	ht_.Print();
	ht_.Delete(13);
	ht_.Print();

	system("pause");
	return 0;
}