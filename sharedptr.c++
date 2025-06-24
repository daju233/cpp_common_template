class sharedptr{
    Object* object
    std::atomic<int> num
    sharedptr(Object object){
        num = 0;
        std::atomic_add(num);
        if(num==1){
            object_space = malloc(sizeof(object))
            object_obj = object{
                //...
            }
            object_space = static_cast<*void>(&object_obj)
            object = static_cast<Object*>(*object_space)
        }
    }
    ~sharedptr(){
        std::atomic_minus(num);
        if(num==0){
            delete Object;
        }
    }
    sharedptr(Object foo){
        std::atomic_add(foo.num);
        num=foo.num;
        object=&(foo.object);
    }   
    sharedptr(Object&& foo){
        num=foo.num;
        object=&(foo.object);
    }
}