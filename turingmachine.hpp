#ifndef __TURING_MACHINE_HPP__
#define __TURING_MACHINE_HPP__

#define DEBUG 0
#include <string>
#include <map>

namespace tmch{
    enum State{ACCEPT, REJECT, HALT, RUNNING};
    enum Exception{STATE_EXISTS, NO_CONNECTION, RULE_EXISTS};
    enum Dir{RIGHT, LEFT};

    class tmConfig{
        private:
            std::string left, state, right;
        public:
            tmConfig();
            ~tmConfig();
            void setRight(std::string right);
            void setLeft(std::string left);
            void setState(std::string state);
            std::string getState() const;
            std::string getRight() const;
            std::string getLeft() const;
            std::string toString() const;
    };

    class tmState{
        private:
            struct Rule{
                Dir dir;
                char c;
                std::string state;
            };

            std::string name;
            std::map<char, Rule> mapping;

            bool hasMapping(char key);
        public:
            tmState(std::string name);
            ~tmState();
            std::string getName() const;
            void addRule(char current, char dest, Dir direction, std::string state);
            void accept(tmConfig *current_config);
    };

    class TuringMachine{
        private:
            tmConfig config;
            std::map<std::string, tmState> states;
            std::string initial_state, accept_state, reject_state; 
            bool stateExists(std::string key);
            bool reject_no_conn = false;
        public:
            State state = HALT;
            TuringMachine();
            ~TuringMachine();
            void setInitial(std::string key);
            void setAccept(std::string key);
            void setReject(std::string key);
            void addState(std::string name);
            tmState &getState(std::string key);
            void load(std::string s);
            void step();
            void setRejectNoConnection(bool v);
            std::string toString() const;
    };
}
std::ostream& operator<< (std::ostream &out, tmch::TuringMachine const &tm);
#endif