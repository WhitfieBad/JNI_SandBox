#include <fstream>
#include <jni.h>
#include <dlfcn.h>

JavaVM *vm = nullptr;
JNIEnv *env = nullptr;

void* func(void* arg) {
    void *handle = dlopen("libjvm.so", RTLD_LAZY);
  	jint (JNICALL * GetJvm) (JavaVM**, jsize, jsize*);
  	GetJvm = (jint (JNICALL*) (JavaVM**, jsize, jsize*)) dlsym(handle, "JNI_GetCreatedJavaVMs");
    auto n_vms = 1;
  	GetJvm(&vm, n_vms, &n_vms);
    vm->AttachCurrentThread(reinterpret_cast<void **>(&env), nullptr);

    jclass classMain = env->FindClass("Main");
    jclass classTest = env->FindClass("TestClass");

    jmethodID methodTest = env->GetStaticMethodID(classMain, "test", "()V");
    env->CallStaticVoidMethod(classMain, methodTest);

    jfieldID hellID = env->GetStaticFieldID(classMain, "testClass", "LTestClass;");
    jobject hell = env->GetStaticObjectField(classMain, hellID);
    env->CallVoidMethod(hell, env->GetMethodID(classTest, "goodBye", "()V"));

    vm->DetachCurrentThread();
    pthread_detach(pthread_self());
    return nullptr;
}

__attribute__((constructor)) static void initialize_navigationBarImages() {
    pthread_t ptid;
    pthread_create(&ptid, nullptr, &func, nullptr);
}

__attribute__((destructor)) static void destroy_navigationBarImages() {

}


