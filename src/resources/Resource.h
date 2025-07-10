#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <memory>

class Resource {
    public:
        Resource();
        virtual ~Resource() {};
        virtual void unload() = 0;
};


#endif // RESOURCE_H