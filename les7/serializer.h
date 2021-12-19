#pragma once

#include "students.pb.h" 
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class IRepository {
    virtual void Open() = 0; // binary deserialization from file
    virtual void Save() = 0; // binary serialization to file
};

class IMethods {
    virtual double GetAverageScore(const students::FullName& name) = 0;
    virtual std::string GetAllInfo(const students::FullName& name) = 0;
    virtual std::string GetAllInfo() = 0;
};

class Serializer : public IRepository, public IMethods
{
public:
    Serializer(const std::string& fileName) :
        m_fileName{ fileName }
    {}
    void CreateGroup();
    void ShowInfo();
private:
    void Open() override;
    void Save() override;
    double GetAverageScore(const students::FullName& name) override;
    std::string GetAllInfo(const students::FullName& name) override;
    std::string GetAllInfo() override;
public:
    std::string m_fileName;
    students::StudentsGroup m_group;
};

