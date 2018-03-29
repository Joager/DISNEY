package com.cubesouls.window;

import java.awt.Color;
import com.cubesouls.window.Console;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class Main {
	public static void main(String[] args) {
		System.out.println("tentando fazer isso funcionar");
		JFrame console = new JFrame("Console++");
		ConsolePanel panel = new ConsolePanel();
		JLabel label = new JLabel("<html>teste</html>");
		JLabel consoleLabel[] = new JLabel[30];
		Console.initConsole(consoleLabel);
        console.setSize(800,800);
        console.getContentPane().setBackground(Color.BLACK);
        console.add(panel);
        console.add(label);
        for (int x = 0; x < 30; x++) {
        	console.add(consoleLabel[x]);
        	System.out.printf("Tentando botar o label de numero %d\n", x);
        }
        console.setLayout(null);
        console.setVisible(true);
        console.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		console.setResizable(false);
		for (int x = 0; x < 30; x++) {
			int y = x * 16 + 30;
        	consoleLabel[x].setLocation(1, y);
        	System.out.println(y);
        	consoleLabel[x].setSize(800, 30);
        }
		label.setLocation(1, 600);
		label.setSize(800, 30);
		Console.mainLoop(consoleLabel);
//		Console.print(console, string);
    }
}
