#include <thread>
#include <string>
#include <mutex>

using namespace std;

mutex g_mu;
bool g_flag;

class A {
public:
    A()
    {
        cout<<"A"<<endl;
    }
  
    virtual ~A()
    {
        // 当析构函数被调用时，需要销毁什么？
        // 释放内存，释放锁，文件描述符
        
    }
  
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
        // 假如执行到这一行时线程crash，g_mu如何释放？
        // 有一种方法是使用C++11中的互斥量管理模板 unique_lock<mutex> lk<g_mu>; lk.unlock() 提前解锁
        g_mu.lock();
        g_flag = false;
        g_mu.unlock();
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


void ThreadFunc()
{
    cout<<"ThreadFunc"<<endl;
}

void ThreadHandleA()
{
   A *a = new A();
   a->Func3();
   loop();
   delete a;
   a = nullptr;
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
}
