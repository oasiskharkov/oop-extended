#include "phoneBook.h"

TEST(TestPerson, operator_less)
{
    Person p1{ "Koto", "Iva", "Ivanovic" };
    Person p2{ "Kotov", "Ivan", "Ivanovich" };
    ASSERT_TRUE(p1.m_name < p2.m_name);
    ASSERT_TRUE(p1.m_surname < p2.m_surname);
    ASSERT_TRUE(p1.m_patronymic < p2.m_patronymic);
    ASSERT_TRUE(p1 < p2);
    Person p3{ "Kozlov", "Ivan", "Ivanovic" };
    ASSERT_FALSE(p3 < p1);
}

TEST(TestPerson, operator_equal)
{
    Person p1{ "Kotov", "Ivan", "Ivanovich" };
    Person p2{ "Kotov", "Ivan", "Ivanovich" };
    ASSERT_EQ(p1.m_name, p2.m_name);
    ASSERT_EQ(p1.m_surname, p2.m_surname);
    ASSERT_EQ(p1.m_patronymic, p2.m_patronymic);
    ASSERT_EQ(p2, p1);
}

TEST(TestPhoneNumber, operator_less)
{
    PhoneNumber pn1{ 16, 465, "9155448", 13 };
    PhoneNumber pn2{ 17, 466, "9155449", 14 };
    ASSERT_LT(pn1.m_addNumber, pn2.m_addNumber);
    ASSERT_LT(pn1.m_cityCode, pn2.m_cityCode);
    ASSERT_LT(pn1.m_countryCode, pn2.m_countryCode);
    ASSERT_LT(pn1.m_number, pn2.m_number);
    ASSERT_LT(pn1, pn2);
    PhoneNumber pn3{ 16, 465, "9155448", 13 };
    PhoneNumber pn4{ 16, 465, "91554481", 13 };
    ASSERT_FALSE(pn4 < pn3);
}

TEST(TestPhoneNumber, operator_equal)
{
    PhoneNumber pn1{ 16, 465, "9155448", 13 };
    PhoneNumber pn2{ 16, 465, "9155448", 13 };
    ASSERT_EQ(pn1.m_addNumber, pn2.m_addNumber);
    ASSERT_EQ(pn1.m_cityCode, pn2.m_cityCode);
    ASSERT_EQ(pn1.m_countryCode, pn2.m_countryCode);
    ASSERT_EQ(pn1.m_number, pn2.m_number);
    ASSERT_EQ(pn1, pn2);
}

class TestPhoneBook : public testing::Test {
protected:
    void SetUp() override {
        std::ifstream inputFile("test.txt");
        testbook = new PhoneBook(inputFile);
    }
    void TearDown() override {
        delete testbook;
    }
    PhoneBook* testbook;
};

TEST_F(TestPhoneBook, get_phone_number)
{    
    const auto& [result1, number1] = testbook->GetPhoneNumber("Zaitsev");
    const auto& [result2, number2] = testbook->GetPhoneNumber("Petrov");
    const auto& [result3, number3] = testbook->GetPhoneNumber("Dubinin");

    ASSERT_STREQ(result1.c_str(), "");
    ASSERT_STREQ(result2.c_str(), "not found");
    ASSERT_STREQ(result3.c_str(), "found more than 1");

    ASSERT_STREQ(number1.value().m_number.c_str(), "4164751");   
}

TEST_F(TestPhoneBook, change_phone_number)
{
    const auto& [result, number] = testbook->GetPhoneNumber("Kotov");
    ASSERT_TRUE(number.has_value());
    ASSERT_STREQ(result.c_str(), "");
    ASSERT_STRNE(number.value().m_number.c_str(), "15344458");
    testbook->ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", std::nullopt });
    const auto& [result4, number4] = testbook->GetPhoneNumber("Kotov");

    ASSERT_STREQ(number4.value().m_number.c_str(), "15344458");
}

TEST_F(TestPhoneBook, sort_by_name)
{
    testbook->SortByName();
    PhoneBook& pb = *testbook;
    const auto& [person1, number1] = pb[0];
    const auto& [person2, number2] = pb[1];
    const auto& [person3, number3] = pb[2];
    const auto& [person4, number4] = pb[3];
    const auto& [person5, number5] = pb[4];

    ASSERT_STREQ(person1.m_surname.c_str(), "Dubinin");
    ASSERT_STREQ(person2.m_surname.c_str(), "Dubinin");
    ASSERT_STREQ(person3.m_surname.c_str(), "Ilin");
    ASSERT_STREQ(person4.m_surname.c_str(), "Kotov");
    ASSERT_STREQ(person5.m_surname.c_str(), "Zaitsev");
}

TEST_F(TestPhoneBook, sort_by_phone)
{
    testbook->SortByPhone();
    PhoneBook& pb = *testbook;
    const auto& [person1, number1] = pb[0];
    const auto& [person2, number2] = pb[1];
    const auto& [person3, number3] = pb[2];
    const auto& [person4, number4] = pb[3];
    const auto& [person5, number5] = pb[4];

    PhoneNumber n1{ 7, 17, "4559767", 12 };
    PhoneNumber n2{ 7, 367, "7508888" };
    PhoneNumber n3{ 7, 473, "7449054", 5 };
    PhoneNumber n4{ 7, 473, "7449054", 5 };
    PhoneNumber n5{ 125, 44, "4164751", 9 };

    ASSERT_EQ(number1, n1);
    ASSERT_EQ(number2, n2);
    ASSERT_EQ(number3, n3);
    ASSERT_EQ(number4, n4);
    ASSERT_EQ(number5, n5);
}

int main()
{
    std::ifstream inputFile("PhoneBook.txt");
    PhoneBook book{inputFile};
    std::cout << book;

    std::cout << "------SortByPhone-------" << std::endl;
    book.SortByPhone();
    std::cout << book;

    std::cout << "------SortByName--------" << std::endl;
    book.SortByName();
    std::cout << book;

    std::cout << "-----GetPhoneNumber-----" << std::endl;
    auto print_phone_number = [&book](const std::string& surname) {
        std::cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (std::get<0>(answer).empty())
        {
            std::cout << std::get<1>(answer).value();
        }  
        else
        {
            std::cout << std::get<0>(answer);
        }
        std::cout << std::endl;
    };

    print_phone_number("Ivanov");
    print_phone_number("Petrov");
    print_phone_number("Solovev");

    std::cout << "----ChangePhoneNumber----" << std::endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", std::nullopt });
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
    std::cout << book;

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
