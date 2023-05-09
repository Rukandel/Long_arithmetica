/*
Программа для длинной арифметики для длинной арифметики
Функционал:
1 - Сравнение  
2 - Сложение 
3 - Вычитание 
4 - Произведение
5 - Факториал до заданного числа
6 - Числа Фебаначчи до заданного числа
6 - Числа Каталана до заданного числа
*/

#include <iostream>
#include<string>
#include<vector>
using namespace std;


class BigInt {
	string digits;
public:

	
	BigInt(unsigned long long n = 0);
	BigInt(string&);
	BigInt(const char*);
	BigInt(BigInt&);


	friend void divide_by_2(BigInt& a);
	friend bool Null(const BigInt&);
	friend int Length(const BigInt&);
	int operator[](const int)const;

	
	BigInt& operator=(const BigInt&);

	// Инкремент и дикремент
	BigInt& operator++();
	BigInt operator++(int temp);
	BigInt& operator--();
	BigInt operator--(int temp);

	// Сложение и вычитание
	friend BigInt& operator+=(BigInt&, const BigInt&);
	friend BigInt operator+(const BigInt&, const BigInt&);
	friend BigInt operator-(const BigInt&, const BigInt&);
	friend BigInt& operator-=(BigInt&, const BigInt&);

	// Опертаторы сравнения
	friend bool operator==(const BigInt&, const BigInt&);
	friend bool operator!=(const BigInt&, const BigInt&);

	friend bool operator>(const BigInt&, const BigInt&);
	friend bool operator>=(const BigInt&, const BigInt&);
	friend bool operator<(const BigInt&, const BigInt&);
	friend bool operator<=(const BigInt&, const BigInt&);

	// Умножение и деление
	friend BigInt& operator*=(BigInt&, const BigInt&);
	friend BigInt operator*(const BigInt&, const BigInt&);
	friend BigInt& operator/=(BigInt&, const BigInt&);
	friend BigInt operator/(const BigInt&, const BigInt&);

	// Деление с остатком
	friend BigInt operator%(const BigInt&, const BigInt&);
	friend BigInt& operator%=(BigInt&, const BigInt&);

	// Степенная функция
	friend BigInt& operator^=(BigInt&, const BigInt&);
	friend BigInt operator^(BigInt&, const BigInt&);

	// Квадратный корень
	friend BigInt sqrt(BigInt& a);

	// Чтение и запись числа
	friend ostream& operator<<(ostream&, const BigInt&);
	friend istream& operator>>(istream&, BigInt&);

	// Понты
	friend BigInt NthCatalan(int n);
	friend BigInt NthFibonacci(int n);
	friend BigInt Factorial(int n);
};

BigInt::BigInt(string& s) {
	digits = "";
	int n = s.size();
	for (int i = n - 1; i >= 0; i--) {
		if (!isdigit(s[i]))
			throw("ERROR");
		digits.push_back(s[i] - '0');
	}
}
BigInt::BigInt(unsigned long long nr) {
	do {
		digits.push_back(nr % 10);
		nr /= 10;
	} while (nr);
}
BigInt::BigInt(const char* s) {
	digits = "";
	for (int i = strlen(s) - 1; i >= 0; i--)
	{
		if (!isdigit(s[i]))
			throw("ERROR");
		digits.push_back(s[i] - '0');
	}
}
BigInt::BigInt(BigInt& a) {
	digits = a.digits;
}

bool Null(const BigInt& a) {
	if (a.digits.size() == 1 && a.digits[0] == 0)
		return true;
	return false;
}
int Length(const BigInt& a) {
	return a.digits.size();
}
int BigInt::operator[](const int index)const {
	if (digits.size() <= index || index < 0)
		throw("ERROR");
	return digits[index];
}
bool operator==(const BigInt& a, const BigInt& b) {
	return a.digits == b.digits;
}
bool operator!=(const BigInt& a, const BigInt& b) {
	return !(a == b);
}
bool operator<(const BigInt& a, const BigInt& b) {
	int n = Length(a), m = Length(b);
	if (n != m)
		return n < m;
	while (n--)
		if (a.digits[n] != b.digits[n])
			return a.digits[n] < b.digits[n];
	return false;
}
bool operator>(const BigInt& a, const BigInt& b) {
	return b < a;
}
bool operator>=(const BigInt& a, const BigInt& b) {
	return !(a < b);
}
bool operator<=(const BigInt& a, const BigInt& b) {
	return !(a > b);
}

BigInt& BigInt::operator=(const BigInt& a) {
	digits = a.digits;
	return *this;
}

BigInt& BigInt::operator++() {
	int i, n = digits.size();
	for (i = 0; i < n && digits[i] == 9; i++)
		digits[i] = 0;
	if (i == n)
		digits.push_back(1);
	else
		digits[i]++;
	return *this;
}
BigInt BigInt::operator++(int temp) {
	BigInt aux;
	aux = *this;
	++(*this);
	return aux;
}

BigInt& BigInt::operator--() {
	if (digits[0] == 0 && digits.size() == 1)
		throw("UNDERFLOW");
	int i, n = digits.size();
	for (i = 0; digits[i] == 0 && i < n; i++)
		digits[i] = 9;
	digits[i]--;
	if (n > 1 && digits[n - 1] == 0)
		digits.pop_back();
	return *this;
}
BigInt BigInt::operator--(int temp) {
	BigInt aux;
	aux = *this;
	--(*this);
	return aux;
}

BigInt& operator+=(BigInt& a, const BigInt& b) { // сумма
	int t = 0, s, i;
	int n = Length(a), m = Length(b);
	if (m > n)
		a.digits.append(m - n, 0);
	n = Length(a);
	for (i = 0; i < n; i++) {
		if (i < m)
			s = (a.digits[i] + b.digits[i]) + t;
		else
			s = a.digits[i] + t;
		t = s / 10;
		a.digits[i] = (s % 10);
	}
	if (t)
		a.digits.push_back(t);
	return a;
}
BigInt operator+(const BigInt& a, const BigInt& b) {
	BigInt temp;
	temp = a;
	temp += b;
	return temp;
}

BigInt& operator-=(BigInt& a, const BigInt& b) { // разность
	if (a < b)
		throw("UNDERFLOW");
	int n = Length(a), m = Length(b);
	int i, t = 0, s;
	for (i = 0; i < n; i++) {
		if (i < m)
			s = a.digits[i] - b.digits[i] + t;
		else
			s = a.digits[i] + t;
		if (s < 0)
			s += 10,
			t = -1;
		else
			t = 0;
		a.digits[i] = s;
	}
	while (n > 1 && a.digits[n - 1] == 0)
		a.digits.pop_back(),
		n--;
	return a;
}
BigInt operator-(const BigInt& a, const BigInt& b) {
	BigInt temp;
	temp = a;
	temp -= b;
	return temp;
}

BigInt& operator*=(BigInt& a, const BigInt& b) // умножение 
{
	if (Null(a) || Null(b)) {
		a = BigInt();
		return a;
	}
	int n = a.digits.size(), m = b.digits.size();
	vector<int> v(n + m, 0);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			v[i + j] += (a.digits[i]) * (b.digits[j]);
		}
	n += m;
	a.digits.resize(v.size());
	for (int s, i = 0, t = 0; i < n; i++)
	{
		s = t + v[i];
		v[i] = s % 10;
		t = s / 10;
		a.digits[i] = v[i];
	}
	for (int i = n - 1; i >= 1 && !v[i]; i--)
		a.digits.pop_back();
	return a;
}
BigInt operator*(const BigInt& a, const BigInt& b) {
	BigInt temp;
	temp = a;
	temp *= b;
	return temp;
}

BigInt& operator/=(BigInt& a, const BigInt& b) { // деление 
	if (Null(b))
		throw("Arithmetic Error: Division By 0");
	if (a < b) {
		a = BigInt();
		return a;
	}
	if (a == b) {
		a = BigInt(1);
		return a;
	}
	int i, lgcat = 0, cc;
	int n = Length(a), m = Length(b);
	vector<int> cat(n, 0);
	BigInt t;
	for (i = n - 1; t * 10 + a.digits[i] < b; i--) {
		t *= 10;
		t += a.digits[i];
	}
	for (; i >= 0; i--) {
		t = t * 10 + a.digits[i];
		for (cc = 9; cc * b > t; cc--);
		t -= cc * b;
		cat[lgcat++] = cc;
	}
	a.digits.resize(cat.size());
	for (i = 0; i < lgcat; i++)
		a.digits[i] = cat[lgcat - i - 1];
	a.digits.resize(lgcat);
	return a;
}
BigInt operator/(const BigInt& a, const BigInt& b) { 
	BigInt temp;
	temp = a;
	temp /= b;
	return temp;
}

BigInt& operator%=(BigInt& a, const BigInt& b) { 
	if (Null(b))
		throw("Arithmetic Error: Division By 0");
	if (a < b) {
		return a;
	}
	if (a == b) {
		a = BigInt();
		return a;
	}
	int i, lgcat = 0, cc;
	int n = Length(a), m = Length(b);
	vector<int> cat(n, 0);
	BigInt t;
	for (i = n - 1; t * 10 + a.digits[i] < b; i--) {
		t *= 10;
		t += a.digits[i];
	}
	for (; i >= 0; i--) {
		t = t * 10 + a.digits[i];
		for (cc = 9; cc * b > t; cc--);
		t -= cc * b;
		cat[lgcat++] = cc;
	}
	a = t;
	return a;
}
BigInt operator%(const BigInt& a, const BigInt& b) { // деление с остатком
	BigInt temp;
	temp = a;
	temp %= b;
	return temp;
}

BigInt& operator^=(BigInt& a, const BigInt& b) {  // возведение в степень
	BigInt Exponent, Base(a);
	Exponent = b;
	a = 1;
	while (!Null(Exponent)) {
		if (Exponent[0] & 1)
			a *= Base;
		Base *= Base;
		divide_by_2(Exponent);
	}
	return a;
}
BigInt operator^(BigInt& a, BigInt& b) {
	BigInt temp(a);
	temp ^= b;
	return temp;
}

void divide_by_2(BigInt& a) {  // возведение в степень двойки
	int add = 0;
	for (int i = a.digits.size() - 1; i >= 0; i--) {
		int digit = (a.digits[i] >> 1) + add;
		add = ((a.digits[i] & 1) * 5);
		a.digits[i] = digit;
	}
	while (a.digits.size() > 1 && !a.digits.back())
		a.digits.pop_back();
}

BigInt sqrt(BigInt& a) { // Вычисление квадратного корня
	BigInt left(1), right(a), v(1), mid, prod;
	divide_by_2(right);
	while (left <= right) {
		mid += left;
		mid += right;
		divide_by_2(mid);
		prod = (mid * mid);
		if (prod <= a) {
			v = mid;
			++mid;
			left = mid;
		}
		else {
			--mid;
			right = mid;
		}
		mid = BigInt();
	}
	return v;
}

BigInt NthCatalan(int n) { // Вычисление Каталана
	BigInt a(1), b;
	for (int i = 2; i <= n; i++)
		a *= i;
	b = a;
	for (int i = n + 1; i <= 2 * n; i++)
		b *= i;
	a *= a;
	a *= (n + 1);
	b /= a;
	return b;
}

BigInt NthFibonacci(int n) { // Вычисление Фибоначчи
	BigInt a(1), b(1), c;
	if (!n)
		return c;
	n--;
	while (n--) {
		c = a + b;
		b = a;
		a = c;
	}
	return b;
}

BigInt Factorial(int n) { // Вычисление факториала
	BigInt f(1);
	for (int i = 2; i <= n; i++)
		f *= i;
	return f;
}

istream& operator>>(istream& in, BigInt& a) {
	string s;
	in >> s;
	int n = s.size();
	for (int i = n - 1; i >= 0; i--) {
		if (!isdigit(s[i]))
			throw("INVALID NUMBER");
		a.digits[n - i - 1] = s[i];
	}
	return in;
}

ostream& operator<<(ostream& out, const BigInt& a) {
	for (int i = a.digits.size() - 1; i >= 0; i--)
		cout << (short)a.digits[i];
	return cout;
}



int main()
{
	setlocale(LC_ALL, "Russian");
	BigInt first = "12345678987654320";
	BigInt second = "987654321";
	BigInt third = "789987654321";
	BigInt fourth = "123456789";
	BigInt fifth = "123454321";

	
	cout << "Количество цифр в первом числе - " << Length(first) << '\n';
	

	if (first == second) {											// Сравнение чисел 1 и 2
		cout << "Первое и второе число равно!\n";
	}
	else
		cout << "Первое и второе число не равны!\n";

	

	if (third < fourth) {										// Сравнение чисел 3 и 4
		cout <<  "Третье число оказалось меньше второго!\n";
	}

	if (fifth > fourth) {
		cout << "Пятое число длиннее четвертого!\n";
	}

															// Вывод всех чисел 
	cout << "Первое число = " << first << '\n';
	cout << "Второе число = " << second << '\n';
	cout << "Третье число = " << third << '\n';
	cout << "Четвертое число = " << fourth << '\n';
	cout << "Пятое число = " << fifth << '\n';
	
	first++;													// Инкремент к 1 числу
	cout << "После инекремента первое число равно:";
	cout << first << '\n';
	
	
	BigInt sum;
	sum = (first + second + third + fourth + fifth);								// Сумма всех чисел 
	cout << "Сумма все заданных чисел равна: "
		<< sum << '\n';
	
	BigInt diff;	

	diff = (first - second);
	cout << "Разность первого и второго числа равна : " << diff << "\n";// Разность 1 и 2


	BigInt multiplication;
	multiplication = first * second * third * fourth * fifth;					 // Произведение
	cout << "Результат умножения все чисел равен = "
		<< multiplication << '\n';


	// Числа Фебоначчи до заданного числа
	cout << "-------------------------Фибоначчи";
		
	for (int i = 0; i <= 10; i++) {
		BigInt Fib;
		Fib = NthFibonacci(i);
		cout << "Фибоначчи " << i << " = " << Fib << '\n';
	}

	// Числа Каталан до заданного числа
	cout << "-------------------------Каталан";
		
	for (int i = 0; i <= 10; i++) {
		BigInt Cat;
		Cat = NthCatalan(i);
		cout << "Каталан " << i << " = " << Cat << '\n';
	}

	// Cчитаем факториал до заданного числа
	cout << "-------------------------Факториал";
	for (int i = 0; i <= 10; i++) {
		BigInt fact;
		fact = Factorial(i);
		cout << "Factorial of "
			<< i << " = ";
		cout << fact << '\n';
	}

}
