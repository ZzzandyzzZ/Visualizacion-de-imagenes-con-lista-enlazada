#include "Imagen_.h"

QImage Imagen_::image() const
{
    return image_;
}

void Imagen_::setImage(const QImage &image)
{
    image_ = image;
}

QString Imagen_::getTitle() const
{
    return title;
}

void Imagen_::setTitle(const QString &value)
{
    title = value;
}

QString Imagen_::getTags() const
{
    return tags;
}

void Imagen_::setTags(const QString &value)
{
    tags = value;
}

Imagen_::Imagen_(){
    title="No declarado";
    tags="Vacio";
}
Imagen_::Imagen_(QImage image,QString title, QString tags):
    image_(image),tags(tags),title(title){


}
