#ifndef __TURING_MACHINE_HPP__
#define __TURING_MACHINE_HPP__

#define DEBUG 0
#include <string>
#include <map>

namespace tmch{
    enum State{ACCEPT, REJECT, HALT, RUNNING};
    enum Exception{STATE_EXISTS, STATE_DOESNT_EXIST, NO_CONNECTION, RULE_EXISTS, RULE_DOES_NOT_EXIST};
    enum Dir{RIGHT, LEFT, STAY};

    /* Class to hold a TM's current configuration */
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

    /* Class used to describe a State of a turing machine*/
    class tmState{
        private:
            struct Rule{
                Dir dir;
                char c;
                std::string state;
            };

            std::string name;
            std::map<char, Rule> mapping;

        private:
            bool hasMapping(char key);
            
        public:
            tmState(std::string name);
            ~tmState();
            std::string getName() const;
            void addRule(char current, char dest, Dir direction, std::string state);
            bool hasRule(char current);
            void deleteRule(char current);
            void changeRule(char current, char dest, Dir direction, std::string state);
            void clear();
            void accept(tmConfig *current_config);
    };

    class TuringMachine{
        private:
            tmConfig config;
            std::map<std::string, tmState> states;
            std::string initial_state, accept_state, reject_state; 
            bool reject_no_conn = false;
        private:
            void clearExcessEmptySpace(std::string &s, int *size);
            void clearExcessEmptySpaceRight(std::string &s, int *size);
            void clearExcessEmptySpaceLeft(std::string &s, int *size);
        public:
            State state = HALT;
            TuringMachine();
            ~TuringMachine();
            tmConfig &getConfig();
            /* Sets the initial state
             * Add's a new state if it doenst already exist
             */
            void setInitial(std::string key);
            bool hasInitial();
            /*
             * Sets the acceptance state of the tm
             * This state shouldn't have any transitions defined
             */
            void setAccept(std::string key);
            bool hasAccept();
            /*
             * Sets the rejection state of the tm
             * This state shouldn't have any transitions defined
             */
            void setReject(std::string key);
            bool hasReject();
            /*
             * Adds a new state of the tm
             */
            void addState(std::string name);
            /*
             * Adds a new state of the tm
             */
            void removeState(std::string name);
            /*
             * Get a state of the tm by it's name
             */
            tmState &getState(std::string key);
            bool stateExists(std::string key);
            void reset();
            /*
             * Loads and input string
             */
            void load(std::string s);
            void step();
            /*
             * Runs the TM until it reaches a final state and returns the number of steps
             * The TM can get stun in an infinite loop depending on how it is configured
             */
            int run();
            void clear();
            /*
             * If true, all undefined transitions will lead to the rejection state
             */
            void setRejectNoConnection(bool v);
            std::string toString() const;
            std::string stateToString() const;
    };
}
std::ostream& operator<< (std::ostream &out, tmch::TuringMachine const &tm);
#endif