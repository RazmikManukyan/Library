#include <iostream>
#include <string>
#include <vector>

class Material {
public:;

    Material(const std::string &title, int publishYear)
            : title(title), publishYear(publishYear), isBorrowed(false) {}

    Material(const Material &oth)
            : title(oth.title), publishYear(oth.publishYear), isBorrowed(oth.isBorrowed) {}

    Material &operator=(const Material &oth) {
        if (this != &oth) {
            title = oth.title;
            publishYear = oth.publishYear;
            isBorrowed = oth.isBorrowed;
        }
        return *this;
    }

    ~Material() = default;;

    std::string getTitle() const { return title; }

    int getPublishYear() const { return publishYear; }

    bool getIsBorrowed() const { return isBorrowed; }

    void setBorrowed(bool value) { isBorrowed = value; }

protected:
    std::string title;
    int publishYear;
    bool isBorrowed;
};

class Book : public Material {
public:
    Book(const std::string &title, int publishYear, const std::string &author, const std::string &genre, int numPage)
            : Material(title, publishYear), author(author), genre(genre), numPages(numPages) {}

    Book(const Book &oth)
            : Material(oth), author(oth.author), genre(oth.genre), numPages(numPages) {}

    Book &operator=(const Book &oth) {
        if (this != &oth) {
            Material::operator=(oth);
            author = oth.author;
            genre = oth.genre;
            numPages = oth.numPages;
        }
        return *this;
    }

    ~Book() = default;;

    std::string getAuthor() const {
        return author;
    }

    std::string getGenre() const {
        return genre;
    }

    int getNumPages() const {
        return numPages;
    }

private:
    std::string author;
    std::string genre;
    int numPages;
};

class Journal : public Material {
public:
    Journal(const std::string &title, int publishYear, const std::string &volume, const std::string &issue,
            const std::string &subject)
            : Material(title, publishYear), volume(volume), issue(issue), subject(subject) {}

    Journal(const Journal &oth)
            : Material(title, publishYear), volume(volume), issue(issue), subject(subject) {};

    Journal &operator=(const Journal &oth) {
        if (this != &oth) {
            Material::operator=(oth);
            volume = oth.volume;
            issue = oth.issue;
            subject = oth.subject;
        }
        return *this;
    }

    ~Journal() = default;;

    std::string getVolume() const {
        return volume;
    }

    std::string getIssue() const {
        return issue;
    }

    std::string getSubject() const {
        return subject;
    }

private:
    std::string volume;
    std::string issue;
    std::string subject;
};

class DVD : public Material {
public:
    DVD(const std::string &title, int publishYear, const std::string &director, int duration)
            : Material(title, publishYear), director(director), duration(duration) {}

    DVD(const DVD &oth)
            : Material(oth), director(oth.director), duration(oth.duration) {}

    DVD &operator=(const DVD &oth) {
        if (this != &oth) {
            Material::operator=(oth);
            director = oth.director;
            duration = oth.duration;
        }
        return *this;
    }

    std::string getDirector() const {
        return director;
    }

    int getDuration() const {
        return duration;
    }

private:
    std::string director;
    int duration;
};

class Library {
public:
    void addMaterial(Material *material) {
        materials.push_back(material);
    }

    void removeMaterial(Material *material) {
        for(auto it = materials.begin(); it != materials.end(); ++it) {
            if(*it == material) {
                materials.erase(it);
                break;
            }
            throw std::invalid_argument("There is not that material! ");
        }
    }

    bool isMaterialAvailable(Material *material) {
        for (const auto& item: materials) {
            if(item == material && !item->getIsBorrowed()) {
                return true;
            }
        }
        return false;
    }

    void borrowMaterial(Material *material) {
        if(isMaterialAvailable(material)) {
            material->setBorrowed(true);
            std::cout << "Successfully borrowed: " << material->getTitle() << std::endl;
        } else {
            std::cout << "The material is not available for borrowing: " << material->getTitle() << std::endl;
        }
    }

    void returnMaterial(Material *material) {
        if(material->getIsBorrowed()) {
            material->setBorrowed(false);
            std::cout << "Successfully returned: " << material->getTitle() << std::endl;
        } else {
            std::cout << "The material is not borrowed: " << material->getTitle() << std::endl;
        }
    }

    std::vector<Material*> searchByTitle(const std::string& title) {
        std::vector<Material*> v;
        for (auto& item: materials) {
            if(item->getTitle() == title) {
                v.push_back(item);
            }
        }
        return v;
    }

    ~Library(){
        for(auto& item: materials) {
            delete item;
        }
    }
private:
    std::vector<Material *> materials;
};

int main() {
    Library library;

    Book* book1 = new Book("Book 1", 2020, "Author 1", "Genre 1", 200);
    Book* book2 = new Book("Book 2", 2021, "Author 2", "Genre 2" , 450);
    Journal* journal1 = new Journal("Journal 1", 2015, "Vol. 1", "Issue 1", "Subject 1");
    Journal* journal2 = new Journal("Journal 2", 2017, "Vol. 2", "Issue 2", "Subject 2");
    DVD* dvd1 = new DVD("DVD 1", 2013, "Director 1" , 3);
    DVD* dvd2 = new DVD("DVD 2", 2001, "Director 2" , 15);

    library.addMaterial(book1);
    library.addMaterial(book2);
    library.addMaterial(journal1);
    library.addMaterial(journal2);
    library.addMaterial(dvd1);
    library.addMaterial(dvd2);

    library.borrowMaterial(book1);
    library.borrowMaterial(journal1);
    library.borrowMaterial(dvd1);
    library.returnMaterial(book1);
    library.returnMaterial(journal1);
    library.returnMaterial(dvd1);


    return 0;
}
