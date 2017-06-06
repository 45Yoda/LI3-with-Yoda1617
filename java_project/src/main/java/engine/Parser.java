package engine;


import java.lang.StringBuffer;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;
import java.util.List;
import java.util.ArrayList;

public class Parser {
    public static void parseDoc(int nsnaps, ArrayList<String> args, CatArtigos artigos, CatContrib contribuidores) throws FileNotFoundException {
        String text = null;
        String[] dados = new String[10];
        int i = 0;
        int n = 0;
        int cbytes = 0;
        int bytes = 0;
        int words = 0;


        try{
            XMLInputFactory factory = XMLInputFactory.newInstance();

            for(;i<nsnaps;i++){
                XMLStreamReader reader = factory.createXMLStreamReader(new FileInputStream(new File(args.get(i))));

                while(reader.hasNext()){
                    int event = reader.next();

                    switch(event){
                        case XMLStreamConstants.END_DOCUMENT:
                            reader.close();
                            break;

                        case XMLStreamConstants.CHARACTERS:
                            text = reader.getText().trim();
                            cbytes = reader.getTextLength();
                            words += countW(text);
                            //Bytes esta bem? REVIEW
                            bytes += cbytes;
                            break;

                        case XMLStreamConstants.END_ELEMENT:
                            switch(reader.getLocalName()){

                                case "title":
                                    dados[0]=text; //titulo do artigo
                                    n=0;
                                    break;

                                case "id":
                                    switch (n){
                                        case 0:
                                            dados[1]=text; //ID artigo
                                            n=1;
                                            break;
                                        case 1:
                                            dados[2]=text;; //ID de Revisão
                                            n=2;
                                            break;
                                        case 2:
                                            dados[3]=text;; //ID de Contribuidor
                                            break;
                                    }

                                case "timestamp":
                                    dados[4]=text;; // Timestamp da revisão
                                    break;

                                case "username":
                                    dados[5]=text;; // Username do Contribuidor
                                    //n=2;
                                    break;

                                case "revision":
                                    dados[6]=text; // Número de palavras
                                    dados[7]=text; // Número de bytes
                                    insereDados(dados,artigos,contribuidores);
                                    break;

                                case XMLStreamReader.END_ELEMENT:

                            }
                            break;
                    }
                }
            }
        }
        catch(XMLStreamException e){System.out.println("Erro");}
    }



private static int countW(String str){
      String[] words = str.split("\\W+");

      if (words.length == 1 && words[0].length() == 0) {
          return 0;
      }

      return words.length;
  }


/*
private static int countW(String str){
    int count = 0;
    int i = 0;

    boolean word = false;
    int eol = str.length() -1 ;

    for(i = 0; i < s.length(); i++){
        if(Character.isLetter(str.charAt(i)) && i != eol){
            word = true;
        }
        else if(!Character.isLetter(str.charAt(i)) && word){
            count ++;
            word = false;
        }
    }
    return count;
}

}*/

public static void insereDados(String[] dados,CatArtigos artigos, CatContrib contribuidores){
    if (artigos.existeArtigo(Long.parseLong(dados[1]))){
        Artigo art = artigos.getArtigo(Long.parseLong(dados[1]));
        //TODO
        Revisao revisao = art.getRevisao(Long.parseLong(data[2]));
        if(art.existeRevisao(Long.parseLong(dados[2]))){
            //TODO conta duplicado?
        }
        else{
            Revisao rev = new Revisao (Long.parseLong(data[2]),data[4])
            art.insereRevisao(rev);
            if(art.getWords()<Long.parseLong(dados[6])){
                art.setWords(Long.parseLong(dados[6]));
            }
            if(art.getBytes()<Long.parseLong(dados[7])){
                art.setBytes(Long.parseLong(dados[7]));
            }
            artigos.insereArtigo(art);
        }
    }

    else{
        Revisao revi = new Revisao (Long.parseLong(dados[2]),dados[4]);
        Artigo arti = new Artigo();
        arti.setTitulo(dados[0]);
        arti.setId(Long.parseLong(dados[1]));
        arti.setWords(Long.parseLong(dados[6]));
        arti.setBytes(Long.parseLong(dados[7]));
        //TODO arti.insereRevisao(revi);
        artigos.insereArtigo(arti);
    }

    //Usar try e catch??? REVIEW
    if(!data[3].isEmpty()){ //Caso dos ips
        Contribuidor cont = new Contribuidor(data[5],1,Long.parseLong(data[3]));
        contribuidores.insereContribuidor(cont);
    }
}