/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ventanas;

import java.applet.Applet;
import java.awt.*;

/**
 *
 * @author adria
 */
public class MiApplet extends Applet {
    //Zona de declaracion
    Button b;
    
    public void init(){ //Equivalente al constructor
    
        this.setBackground(Color.blue);
        
        //Zona de instanciación
        b = new Button("Pulsame");
        
        //Zona de agregación
        add(b);
        
    }//Init
    
    public void paint(Graphics g){
        g.drawString("Hoy es meircoles", 30, 30);
        
        g.drawRect(100, 100, 200, 200);
        
        g.fillRoundRect(110, 110, 100, 100, 100, 100);
    }
    
}//Fin
