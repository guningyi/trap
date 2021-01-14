#include <thread>

using namespace std;

class A {
public:
    OnHandleAction()
    {   
        // error, 非静态函数不能用来启动线程
        thread threadFunc2(ThreadFunc);
        threadFunc2.start();
    }

private:
    void ThreadFunc2()
    {
        cout<<"ThreadFunc"<<endl;
    }
    
    void Func3()
    {
        cout<<"Func3"<<endl;
    }
    
    void loop()
    {
        while (condition) {
            cout<<"I am Func3"<<endl;
            sleep(10);
        }
    }
};


A *g_a = nullptr;

void ThreadFunc()
{
    cout<<"ThreadFunc"<<endl;
}

void ThreadHandleA()
{
   g_a = new A();
   g_a->Func3();
   loop();
   delete g_a;
   g_a = nullptr;
}

void UseA(A* a)
{
    if (a != nullptr) {
        a->Func3();
    }
}


int main()
{
   // it's ok
   thread threadFunc(ThreadFunc);
   threadFunc.start();
   // 注意这里不detach走不到下面
   threadFunc.detach();
   
   // it's ok
   thread threadHandleA(ThreadHandleA);
   threadHandleA.start();
   threadHandleA.detach();
   
   // not work, 大概率会拿到一个空指针 g_a
   thread useA(UseA, g_a);
   useA.start();
   useA.detach();
}
