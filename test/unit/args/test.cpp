//
// Created by lukemartinlogan on 8/30/20.
//

/*
 * String, StringMap, int, float, and size args
 * Option assertion
 * Default arguments
 * Invalid arguments
 * Empty param types
 * */

#include <common/arguments.h>
#include <assert.h>

enum class TestCases {
    kArgConv,kArgList,kDefaultArgs,kInvalidArgs,kNoParamArgs
};

class ExampleArgs : public common::args::ArgMap {
private:
    void VerifyArgs(void) {
        AssertOptIsSet("-test");
        switch(static_cast<TestCases>(GetIntOpt("-test"))) {
            case TestCases::kArgConv: {
                AssertOptIsSet("-a");
                AssertOptIsSet("-b");
                AssertOptIsSet("-c");
                AssertOptIsSet("-d");

                std::string a = GetStringOpt("-a");
                int b = GetIntOpt("-b");
                size_t c = GetSizeOpt("-c");
                float d = GetFloatOpt("-d");

                assert(a.compare("hello") == 0);
                assert(b == 24245);
                assert(c == 35*(1<<10));
                assert(d == 2.0);
                break;
            }
            case TestCases::kArgList: {
                AssertOptIsSet("-b");
                std::list<int> bs = GetIntOpts("-b");
                assert(bs.size() == 3);
                for(int &b : bs) {
                    assert(b == 24245);
                }
                break;
            }
            case TestCases::kDefaultArgs: {
                AssertOptIsSet("-e");
                std::list<int> es = GetIntOpts("-e");
                assert(es.size() == 3);
                for(int &e : es) {
                    assert(e == 24245);
                }
                int f = GetIntOpt("-f");
                assert(f == 24245);
                break;
            }
            case TestCases::kNoParamArgs: {
                AssertOptIsSet("-g");
                AssertOptIsSet("-h");
                break;
            }
        }
    }

public:
    void Usage(void) {
        std::cout << "Usage: ./test -[param-id] [value] ..." << std::endl;
        std::cout << "" << std::endl;

        std::cout << "-test [string]: Which test this is" << std::endl;
        std::cout << "   arg_conv" << std::endl;
        std::cout << "   arg_list" << std::endl;
        std::cout << "   default_args" << std::endl;
        std::cout << "   invalid_args" << std::endl;
        std::cout << "   no_param_args" << std::endl;
        std::cout << "" << std::endl;

        std::cout << "-a hello" << std::endl;
        std::cout << "-b 24245" << std::endl;
        std::cout << "-c 35k" << std::endl;
        std::cout << "-d 2.0" << std::endl;
        std::cout << "-e 25" << std::endl;

    }
    ExampleArgs(int argc, char **argv) {
        AddOpt("-test", common::args::ArgType::kStringMap);
        AddStringMapVal("-test", "arg_conv", static_cast<int>(TestCases::kArgConv));
        AddStringMapVal("-test", "arg_list", static_cast<int>(TestCases::kArgList));
        AddStringMapVal("-test", "default_args", static_cast<int>(TestCases::kDefaultArgs));
        AddStringMapVal("-test", "invalid_args", static_cast<int>(TestCases::kInvalidArgs));
        AddStringMapVal("-test", "no_param_args", static_cast<int>(TestCases::kNoParamArgs));
        AddOpt("-a", common::args::ArgType::kString);
        AddOpt("-b", common::args::ArgType::kInt);
        AddOpt("-c", common::args::ArgType::kSize);
        AddOpt("-d", common::args::ArgType::kFloat);
        AddOpt("-e", common::args::ArgType::kInt, 0);
        AddOpt("-f", common::args::ArgType::kInt, 24245);
        AddOpt("-g");
        AddOpt("-h");
        try {
            ArgIter(argc, argv);
        }
        catch(...) {
            if(static_cast<TestCases>(GetIntOpt("-test")) != TestCases::kInvalidArgs) {
                throw 1;
            } else {
                exit(EXIT_SUCCESS);
            }
        }
        if(static_cast<TestCases>(GetIntOpt("-test")) == TestCases::kInvalidArgs) {
            exit(EXIT_FAILURE);
        }
        VerifyArgs();
    }
};

int main(int argc, char **argv)
{
    ExampleArgs args(argc, argv);
}