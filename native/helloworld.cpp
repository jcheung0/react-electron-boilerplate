#include <node.h>
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include "MyObject.h"

namespace demo{
	
	using namespace std;
	using namespace v8;
	using v8::FunctionCallbackInfo;
	using v8::Isolate;
	using v8::Local;
	using v8::Object;
	using v8::String;
	using v8::Value;

	void Method(const FunctionCallbackInfo<Value>& args){
		Isolate* isolate = args.GetIsolate();
		args.GetReturnValue().Set(String::NewFromUtf8(isolate,"world"));
	}		
	
	void RegisterModule(v8::Handle<v8::Object> target){
    	cout << "HELLO WORLD" << endl;        
    }

    void Add(const FunctionCallbackInfo<Value>& args) {
	  Isolate* isolate = args.GetIsolate();

	  // Check the number of arguments passed.
	  if (args.Length() < 2) {
	    // Throw an Error that is passed back to JavaScript
	    isolate->ThrowException(Exception::TypeError(
	        String::NewFromUtf8(isolate, "Wrong number of arguments")));
	    return;
	  }

	
	  // Check the argument types
	  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
	    isolate->ThrowException(Exception::TypeError(
	        String::NewFromUtf8(isolate, "Wrong arguments")));
	    return;
	  }

	  // Perform the operation
	  double value = args[0]->NumberValue() + args[1]->NumberValue();
	  Local<Number> num = Number::New(isolate, value);

	  // Set the return value (using the passed in
	  // FunctionCallbackInfo<Value>&)
	  args.GetReturnValue().Set(num);
	}

	void RunCallback(const FunctionCallbackInfo<Value>& args) {
	  Isolate* isolate = args.GetIsolate();
	  Local<Function> cb = Local<Function>::Cast(args[0]);
	  const unsigned argc = 1;
	  Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "hello world") };
	  cb->Call(Null(isolate), argc, argv);
	}

	void MyFunction(const FunctionCallbackInfo<Value>& args) {
	  Isolate* isolate = args.GetIsolate();
	  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "hello world"));
	}

	void CreateFunction(const FunctionCallbackInfo<Value>& args) {
	  Isolate* isolate = args.GetIsolate();

	  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, MyFunction);
	  Local<Function> fn = tpl->GetFunction();

	  // omit this to make it anonymous
	  fn->SetName(String::NewFromUtf8(isolate, "theFunction"));

	  args.GetReturnValue().Set(fn);
	}
	void init(Local<Object> exports){
		NODE_SET_METHOD(exports,"register",Method);
		NODE_SET_METHOD(exports,"add",Add);
		NODE_SET_METHOD(exports,"callback",RunCallback);
				//NODE_SET_METHOD(exports,"Register",RegisterModule);

		MyObject::Init(exports);
	
	}

	  void CreateObject(const FunctionCallbackInfo<Value>& args) {
		  Isolate* isolate = args.GetIsolate();

		  Local<Object> obj = Object::New(isolate);
		  obj->Set(String::NewFromUtf8(isolate, "msg"), args[0]->ToString());

		  args.GetReturnValue().Set(obj);
		}

	

	NODE_MODULE(addon, init)

	//NODE_MODULE(helloworld,RegisterModule)
	



}




