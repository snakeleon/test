#include <iostream>
#include <map>
#include <string>

int main()
{
    std::map<std::string, float> students;
    students["Kate"] = 4.0;
    students["Tom"] = 8.0;
    students["Latin"] = 10.0;

    for (auto &i:students)
    {
        // i.second = 88;
        std::cout<< i.first <<" score is "<< i.second << std::endl;
    }
    return 0;
}
