
#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <memory>
#include <string>
#include <unordered_map>
#include <list>
#include <memory>
#include <iostream>

namespace common::args {

class Arg;
class StringArg;
class IntArg;
class FloatArg;
class SizeArg;

enum class ArgType {
    kNone, kString, kStringMap, kInt, kFloat, kSize
};

class Arg {
protected:
    std::string opt_name_;
    ArgType type_ = ArgType::kNone;
    bool is_set_ = false;
    bool use_default_ = false;
public:
    Arg(std::string opt_name) : opt_name_(opt_name) {};
    bool IsSet() const { return is_set_; }
    ArgType GetType() const { return type_; }
    virtual int Add() { throw 1; };
    virtual int Add(std::string arg) { throw 1; };
    virtual void AddStringMapVal(std::string val, int id) { throw 1; };
    virtual std::string &GetStringOpt() { throw 1; };
    virtual std::list<std::string> &GetStringOpts() { throw 1; };
    virtual int GetIntOpt() { throw 1; };
    virtual std::list<int> &GetIntOpts() { throw 1; };
    virtual float GetFloatOpt() { throw 1; };
    virtual std::list<float> &GetFloatOpts() { throw 1; };
    virtual size_t GetSizeOpt() { throw 1; };
    virtual std::list<size_t> &GetSizeOpts() { throw 1; };
    virtual ~Arg() = default;
};

typedef std::unique_ptr<Arg> ArgPtr;

class NoneArg : public Arg {
public:
    NoneArg(std::string opt_name) : Arg(opt_name) {}
    int Add() { is_set_ = true; return 0; }
};

class StringArg : public Arg {
private:
    std::list<std::string> args_;
public:
    StringArg(std::string opt_name) : Arg(opt_name) { type_ = ArgType::kString; };
    StringArg(std::string opt_name, std::string dval) : Arg(opt_name) {
        type_ = ArgType::kString;
        args_.emplace_back(dval);
        is_set_ = true;
        use_default_ = true;
    };
    int Add(std::string arg) override {
        if(use_default_) {
            args_.pop_front();
            use_default_ = false;
        }
        args_.emplace_back(arg);
        is_set_ = true;
        return 1;
    }
    std::string &GetStringOpt() override { if(is_set_) return args_.back(); else throw 1; }
    std::list<std::string> &GetStringOpts() override { if(is_set_) return args_; else throw 1; }
};

class StringMapArg : public Arg {
private:
    std::unordered_map<std::string, int> arg_map_;
    std::list<int> args_;

public:
    StringMapArg(std::string opt_name) : Arg(opt_name) { type_ = ArgType::kStringMap; };
    StringMapArg(std::string opt_name, int dval) : Arg(opt_name) {
        type_ = ArgType::kStringMap;
        args_.emplace_back(dval);
        is_set_ = true;
        use_default_ = true;
    };
    void AssertArgExists(std::string &arg) {
        if(arg_map_.find(arg) == arg_map_.end()) {
            std::cout << "Invalid input to " << opt_name_ << ": " << arg << std::endl;
            throw 1;
        }
    }
    int Add(std::string arg) override {
        if(use_default_) {
            args_.pop_front();
            use_default_ = false;
        }
        AssertArgExists(arg);
        args_.emplace_back(arg_map_[arg]);
        is_set_ = true;
        return 1;
    }
    void AddStringMapVal(std::string val, int id) override { arg_map_[val] = id; }
    int GetIntOpt() override { if(is_set_) return args_.back(); else throw 1; };
    std::list<int> &GetIntOpts() override { if(is_set_) return args_; else throw 1; };
};

class IntArg : public Arg {
private:
    std::list<int> args_;
public:
    IntArg(std::string opt_name) : Arg(opt_name) { type_ = ArgType::kInt; };
    IntArg(std::string opt_name, int dval) : Arg(opt_name) {
        type_ = ArgType::kInt;
        args_.emplace_back(dval);
        is_set_ = true;
        use_default_ = true;
    };
    int Add(std::string arg) override {
        if(use_default_) {
            args_.pop_front();
            use_default_ = false;
        }
        args_.emplace_back(std::stoi(arg));
        is_set_ = true;
        return 1;
    }
    int GetIntOpt() override { if(is_set_) return args_.back(); else throw 1; };
    std::list<int> &GetIntOpts() override { if(is_set_) return args_; else throw 1; };
};

class FloatArg : public Arg {
private:
    std::list<float> args_;
public:
    FloatArg(std::string opt_name) : Arg(opt_name) { type_ = ArgType::kFloat; };
    FloatArg(std::string opt_name, float dval) : Arg(opt_name) {
        type_ = ArgType::kFloat;
        args_.emplace_back(dval);
        is_set_ = true;
        use_default_ = true;
    };
    int Add(std::string arg) override {
        if(use_default_) {
            args_.pop_front();
            use_default_ = false;
        }
        args_.emplace_back(std::stof(arg));
        is_set_ = true;
        return 1;
    }
    float GetFloatOpt() override { if(is_set_) return args_.back(); else throw 1; };
    std::list<float> &GetFloatOpts() override { if(is_set_) return args_; else throw 1; };
};

class SizeArg : public Arg {
private:
    std::list<size_t> args_;
    size_t ToSize(std::string arg) {
        char c = arg[arg.length() - 1];
        if ((c == 'k') || (c == 'K')) {
            return std::stoul(arg) * (1ul<<10);
        }
        else if ((c == 'm') || (c == 'M')) {
            return std::stoul(arg) * (1ul<<20);
        }
        else if ((c == 'g') || (c == 'G')) {
            return std::stoul(arg) * (1ul<<30);
        }
        return std::stoul(arg);
    }
public:
    SizeArg(std::string opt_name) : Arg(opt_name) { type_ = ArgType::kSize; };
    SizeArg(std::string opt_name, size_t dval) : Arg(opt_name) {
        type_ = ArgType::kSize;
        args_.emplace_back(dval);
        is_set_ = true;
        use_default_ = true;
    };
    int Add(std::string arg) override {
        if(use_default_) {
            args_.pop_front();
            use_default_ = false;
        }
        args_.emplace_back(ToSize(arg));
        is_set_ = true;
        return 1;
    }
    size_t GetSizeOpt() override { if(is_set_) return args_.back(); else throw 1; };
    std::list<size_t> &GetSizeOpts() override { if(is_set_) return args_; else throw 1; };
};

class ArgFactory {
public:
    static ArgPtr Get(std::string opt_name, ArgType type) {
        switch (type) {
            case ArgType::kNone: {
                return std::make_unique<NoneArg>(opt_name);
            }
            case ArgType::kString: {
                return std::make_unique<StringArg>(opt_name);
            }
            case ArgType::kStringMap: {
                return std::make_unique<StringMapArg>(opt_name);
            }
            case ArgType::kInt: {
                return std::make_unique<IntArg>(opt_name);
            }
            case ArgType::kFloat: {
                return std::make_unique<FloatArg>(opt_name);
            }
            case ArgType::kSize: {
                return std::make_unique<SizeArg>(opt_name);
            }
        }
    }
    static ArgPtr Get(std::string opt_name, ArgType type, std::string dval) {
        switch(type) {
            case ArgType::kString: {
                return std::make_unique<StringArg>(opt_name, dval);
            }
        }
    }
    static ArgPtr Get(std::string opt_name, ArgType type, int dval) {
        switch(type) {
            case ArgType::kStringMap: {
                return std::make_unique<StringMapArg>(opt_name, dval);
            }
            case ArgType::kInt: {
                return std::make_unique<IntArg>(opt_name, dval);
            }
        }
    }
    static ArgPtr Get(std::string opt_name, ArgType type, float dval) {
        switch(type) {
            case ArgType::kFloat: {
                return std::make_unique<FloatArg>(opt_name, dval);
            }
        }
    }
    static ArgPtr Get(std::string opt_name, ArgType type, size_t dval) {
        switch(type) {
            case ArgType::kSize: {
                return std::make_unique<SizeArg>(opt_name, dval);
            }
        }
    }
};

class ArgMap {
protected:
    std::unordered_map<std::string, ArgPtr> args_;

    template<typename ...Args>
    void AddOpt(std::string opt, ArgType type = ArgType::kNone, Args... args) {
        args_.emplace(opt, std::move(ArgFactory::Get(opt, type, args...)));
    }

    void AddStringMapVal(std::string opt, std::string val, int id) {
        AssertOptExists(opt);
        args_[opt]->AddStringMapVal(val, id);
    }

    void ArgIter(int argc, char **argv) {
        for(int i = 1; i < argc; ++i) {
            std::string arg_str = argv[i];
            if (argv[i][0] != '-') {
                arg_str = "";
            }
            AssertOptExists(arg_str);
            ArgPtr &arg = args_[arg_str];
            if((arg->GetType() != ArgType::kNone) && (i+1 < argc)) {
                i += arg->Add(argv[i + 1]);
            }
            else if(arg->GetType() == ArgType::kNone) {
                i += arg->Add();
            }
            else {
                throw 1;
            }
        }
    }

    virtual void VerifyArgs(void) = 0;

public:
    ArgMap() = default;

    bool OptExists(std::string opt) {
        return (args_.find(opt) != args_.end());
    }

    void AssertOptExists(std::string opt) {
        if(!OptExists(opt)) {
            std::cout << "Invalid argument: " << opt << std::endl;
            throw 1;
        }
    }

    bool OptIsSet(std::string opt) {
        if(!OptExists(opt)) {
            return false;
        }
        return args_[opt]->IsSet();
    }

    void AssertOptIsSet(std::string opt) {
        AssertOptExists(opt);
        if(!OptIsSet(opt)) {
            std::cout << opt << " is not set, but is required" << std::endl;
            Usage();
            throw 1;
        }
    }

    void AssertOptIsNotSet(std::string opt) {
        if(OptIsSet(opt)) {
            std::cout << opt << " is set, but is not supposed to be" << std::endl;
            Usage();
            throw 1;
        }
    }

    std::string &GetStringOpt(std::string opt) { AssertOptIsSet(opt); return args_[opt]->GetStringOpt(); }
    std::list<std::string> &GetStringOpts(std::string opt) { AssertOptIsSet(opt); return args_[opt]->GetStringOpts(); }
    int GetIntOpt(std::string opt) { AssertOptIsSet(opt); return args_[opt]->GetIntOpt(); }
    std::list<int> &GetIntOpts(std::string opt) { AssertOptIsSet(opt); args_[opt]->GetIntOpts(); }
    float GetFloatOpt(std::string opt) { AssertOptIsSet(opt); return args_[opt]->GetFloatOpt(); }
    std::list<float> &GetFloatOpts(std::string opt) { AssertOptIsSet(opt); return args_[opt]->GetFloatOpts(); }
    size_t GetSizeOpt(std::string opt) { AssertOptIsSet(opt); return args_[opt]->GetSizeOpt(); }
    std::list<size_t> &GetSizeOpts(std::string opt) { AssertOptIsSet(opt); return args_[opt]->GetSizeOpts(); }

    virtual void Usage(void) = 0;
};

}

#endif