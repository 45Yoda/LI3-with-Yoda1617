package engine;

import java.util.Comparator;
import java.io.Serializable;

public class ComparatorWords implements Comparator<Artigo>{

    public int compare(Artigo a1, Artigo a2){
            long words1 = a1.getWords();
            long words2 = a2.getWords();
            long id1 = a1.getId();
            long id2 = a2.getId();


            if(words1 < words2) return 1;
            if(words1 > words2) return -1;
            else
                return Long.compare(id1,id2);
   }
}
