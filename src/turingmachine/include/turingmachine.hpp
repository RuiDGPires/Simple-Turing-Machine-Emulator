#ifndef __TURING_MACHINE_HPP__
#define __TURING_MACHINE_HPP__

#define DEBUG 0
#include <string>
#include <map>

namespace tmch{
    enum State{ACCEPT, REJECT, HALT, RUNNING};
    enum Exception{STATE_EXISTS, NO_CONNECTION, RULE_EXISTS};
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
            bool reject_no_conn = false;
        public:
            State state = HALT;
            TuringMachine();
            ~TuringMachine();

            /* Sets the initial state
             * Add's a new state if it doenst already exist
             */
            void setInitial(std::string key);

            /*
             * Sets the acceptance state of the tm
             * This state shouldn't have any transitions defined
             */
            void setAccept(std::string key);
            /*
             * Sets the rejection state of the tm
             * This state shouldn't have any transitions defined
             */
            void setReject(std::string key);
            /*
             * Adds a new state of the tm
             */
            void addState(std::string name);
            /*
             * Get a state of the tm by it's name
             */
            tmState &getState(std::string key);
            bool stateExists(std::string key);
            /*
             * Loads and input string
             */
            void load(std::string s);
            void step();
            /*
             * Runs the TM until it reaches a final state
             * The TM can get stun in an infinite loop depending on how it is configured
             */
            void run();
            /*
             * If true, all undefined transitions will lead to the rejection state
             */
            void setRejectNoConnection(bool v);
            std::string toString() const;
    };
}
std::ostream& operator<< (std::ostream &out, tmch::TuringMachine const &tm);
#endif