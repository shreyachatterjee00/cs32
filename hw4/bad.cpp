void removeBad(list<Movie*>& li)
{
    list <Movie *> :: iterator it = li.begin();
    
        for (; it != li.end(); it++) {
            Movie * m = * it;
            if (m->rating() < 55) {
                destroyedOnes.push_back(m->rating());
                li.erase(it);
                it--;
            }
            
        }
}

