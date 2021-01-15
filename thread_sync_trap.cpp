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
    
   // 如果主线程可以block，可以这样写。
   while (g_a == nullptr) {
       sleep(5); // 睡眠一会儿
   }
   // A对象构造完毕后再执行新的线程 
   thread useA(UseA, g_a);
   useA.start();
   useA.detach();
   
   // 另一个简洁的写法，既然主线程在这里可以block，也可以不起线程。
   // 如果业务场景中不存在lionDb重配置的情况。直接函数block主线程
   while (g_a == nullptr) {
       sleep(5);
   }
   UseA(g_a); 

   
   // 如果主线程不能block，该如何写？
   
   
}
