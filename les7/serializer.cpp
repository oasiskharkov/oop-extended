#include "serializer.h"

void Serializer::CreateGroup()
{
	students::FullName fn1;
	fn1.set_name("Ivan");
	fn1.set_surname("Petrov");
	fn1.set_patronymic("Nikolaevich");

	students::FullName fn2;
	fn2.set_name("Petr");
	fn2.set_surname("Ivanov");
	fn2.set_patronymic("Semenovich");

	students::FullName fn3;
	fn3.set_name("Zoya");
	fn3.set_surname("Nikolaeva");
	fn3.set_patronymic("Petrovna");

	students::Student st1;
	*st1.mutable_fullname() = fn1;

	students::Student st2;
	*st2.mutable_fullname() = fn2;

	students::Student st3;
	*st3.mutable_fullname() = fn3;

	double av1 = 0.;
	double av2 = 0.;
	double av3 = 0.;
	for (int i = 0; i < 10; ++i)
	{
		int grade1 = rand() % 5 + 1;
		av1 += grade1;
		st1.add_grades(grade1);
		int grade2 = rand() % 5 + 1;
		av2 += grade2;
		st2.add_grades(grade2);
		int grade3 = rand() % 5 + 1;
		av3 += grade3;
		st3.add_grades(grade3);
	}

	st1.set_average(av1 / 10.);
	st2.set_average(av2 / 10.);
	st3.set_average(av3 / 10.);
	
	m_group.mutable_students()->Add(std::move(st1));
	m_group.mutable_students()->Add(std::move(st2));
	m_group.mutable_students()->Add(std::move(st3));

	Save();
}

void Serializer::ShowInfo()
{
	Open();
	std::cout << GetAllInfo();
}

void Serializer::Open()
{
	std::ifstream in(m_fileName, std::ios_base::binary);
	if (in.is_open())
	{
		m_group.clear_students();
		m_group.ParseFromIstream(&in);
		in.close();
	}
	else
	{
		throw std::logic_error("Can't open input file: " + m_fileName);
	}
}

void Serializer::Save()
{
	std::ofstream out(m_fileName, std::ios_base::binary);
	if (out.is_open())
	{
		m_group.SerializeToOstream(&out);
		out.close();
	}
	else
	{
		throw std::logic_error("Can't open output file: " + m_fileName);
	}
}

double Serializer::GetAverageScore(const students::FullName& name)
{
	for (const auto& st : m_group.students())
	{
		const auto& fname = st.fullname();
		if (std::tie(fname.surname(), fname.name(), fname.patronymic()) == std::tie(name.surname(), name.name(), name.patronymic()))
		{
			return st.average();
		}
	}
	return 0.;
}

std::string Serializer::GetAllInfo(const students::FullName& name)
{
	for (const auto& st : m_group.students())
	{
		const auto& fname = st.fullname();
		std::stringstream ss;
		if (std::tie(fname.surname(), fname.name(), fname.patronymic()) == std::tie(name.surname(), name.name(), name.patronymic()))
		{
			ss << fname.name() << " " << fname.patronymic() << " " << fname.surname() << ": " << st.average();
			return ss.str();
		}
	}
	return "";
}

std::string Serializer::GetAllInfo()
{
	std::stringstream ss;
	for (const auto& st : m_group.students())
	{
		const auto& fname = st.fullname();
		ss << fname.name() << " " << fname.patronymic() << " " << fname.surname() << ": " << st.average() << std::endl;
	}
	return ss.str();
}
