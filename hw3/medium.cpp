//
//  main.cpp
//  HW3
//
//  Created by Shreya Chatterjee on 5/2/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

class Medium { //base class
    //abstract
public:
    //constructor, destructor
    //constructor parameter: string id
    Medium(string id) {
        m_id = id;
    }
    
    //virtual destructor: prints things
    virtual ~Medium() {};
    
    //connect: prints way of talking, such as 'tweet' 'call'
    //pure virtual: how would this class know the method of talking
    virtual string connect() const = 0;
    
    //id: prints id
    //doesn't need to be implemented in other classes
    string id() const {
        return m_id;
    }
    
    //transmit: prints prints way of msg, such as 'text' 'voice' and the msg
    virtual string transmit(string message) const {
        string sendMsg;
        sendMsg = "text: " + message;
        return sendMsg;
    }
    
private:
    string m_id;
};

class Phone : public Medium {
public:
    
    Phone(string number, CallType callType)
    : Medium(number), m_callType(callType) {
        
    }
    
    virtual string connect() const {
        return "Call";
    }
    
    string transmit(string message) const {
        string sendMsg;
        if (m_callType == VOICE) {
            sendMsg = "voice: ";
        }
        else if (m_callType == TEXT) {
            sendMsg = "text: ";
        }
        sendMsg += message;
        return sendMsg;
    }
    
    ~Phone () {
        cout << "Destroying the phone " << id() << "." << endl;
    }
    
private:
    CallType m_callType;
    
};
       
class EmailAccount : public Medium {

public:
    EmailAccount(string email)
    : Medium (email) {
        
    }
    
    virtual string connect () const {
        return "Email";
    }
    
    ~EmailAccount() {
        cout << "Destroying the email account " << id() << "." << endl;
    }
    
};

class TwitterAccount : public Medium {
    
public:
    TwitterAccount(string acc)
    : Medium(acc) {
        
    }
    
    virtual string connect () const {
        return "Tweet";
    }
    
    ~TwitterAccount() {
        cout << "Destroying the Twitter account " << id() << "." << endl;
    }
};




