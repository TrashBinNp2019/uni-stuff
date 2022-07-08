#ifndef FIOMANAGER_H
#define FIOMANAGER_H

#include "data.h"


// Abstract file IO manager
class FIOManager
{
public:
    FIOManager( const QString& );

    virtual void read(Data&) = 0;
    virtual void write(const Data&) = 0;

protected:
    QString filepath;
};


// File IO manager implementation for XML format
class FIOManagerXML : public FIOManager
{
public:
    FIOManagerXML( const QString & );

    void read(Data&);
    void write(const Data&);
};


// File IO manager implementation for JSON format
class FIOManagerJSON : public FIOManager
{
public:
    FIOManagerJSON( const QString & );

    void read(Data&);
    void write(const Data&);
};


// Factory pattern implementation for serving file IO managers
class FIOManagerFactory {
public:
    enum FileFormat { XML, JSON };
    FIOManagerFactory();

    std::unique_ptr<FIOManager> getFIOManager(FileFormat format, const QString& );
private:
    FileFormat format;
};

#endif // FIOMANAGER_H
