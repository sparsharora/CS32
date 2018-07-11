void listAll(const Class* c, string path)  // two-parameter overload
{
    
    cout<<c->name()<<endl;
    for (int i=0; i<c->subclasses().size(); i++)
    {
        cout<<path<<c->name()<<"=>";
        listAll(c->subclasses()[i], path+c->name()+"=>");
    }
}