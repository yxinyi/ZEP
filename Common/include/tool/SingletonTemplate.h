#pragma once


template <class T>
class Singleton {
public:
    static T* getInstance(){
        if(!m_instance){
            m_instance = new T;
        }
        return m_instance;
    }
private:
    static T* m_instance;
};

template<class T>
T* Singleton<T>::m_instance = nullptr;
