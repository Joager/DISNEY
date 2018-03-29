package com.cubesouls.window;

import java.util.Random;

import javax.swing.JFrame;
import javax.swing.JLabel;

public class Console {
	
	public static String[] backup = new String[30];
	
	public static String backupConsoleLine(JLabel[] label, int x) {
		String str2 = "";
		str2 = label[x].getText();
		return str2;
	}
	
	public static void setConsoleLine(JLabel[] label, int line, String str) {
		label[line].setText(str);
		backup[line] = backupConsoleLine(label, line);
	}
	
	public static String getConsoleLine(JLabel[] label, int line) {
		return backup[line];
	}

/*
	public static String clearConsoleLine(String line) {
		
		return line;
	}
*/	
	public static String selectRandomColor(char[] line) {
		String color = "erro";
		String[] carray = new String[line.length];
		int rnd = 0;
		Random random = new Random();
		StringBuilder sb = new StringBuilder();
		sb.append("<html>");
		for (int x = 0; x < line.length; x++) {
			rnd = random.nextInt(6);
			switch(rnd) {
				case 0:
					color = String.format("<font color='red'>%c</font>", line[x]);
					System.out.println(rnd);
					break;
				case 1:
					color = String.format("<font color='orange'>%c</font>", line[x]);
					System.out.println(rnd);
					break;
				case 2:
					color = String.format("<font color='yellow'>%c</font>", line[x]);
					System.out.println(rnd);
					break;
				case 3:
					color = String.format("<font color='green'>%c</font>", line[x]);
					System.out.println(rnd);
					break;
				case 4:
					color = String.format("<font color='cyan'>%c</font>", line[x]);
					System.out.println(rnd);
					break;
				case 5:
					color = String.format("<font color='indigo'>%c</font>", line[x]);
					System.out.println(rnd);
					break;
				case 6:
					color = String.format("<font color='violet'>%c</font>", line[x]);
					System.out.println(rnd);
					break;
			}
			carray[x] = color;
		}
//		String str2 = String.valueOf(line);
		for (int x = 0; x < line.length; x++) {
			sb.append(carray[x]);
		}
		sb.append("</html>");
		color = sb.toString();
		System.out.println(color);
		return color;
	}
	
	public static String rainbowfy(String line) {
		char[] strchar = line.toCharArray();
		line = selectRandomColor(strchar);
		return line;
	}
	
	
	public static void print(JFrame frame, String string) {
		JLabel label = new JLabel();
		label.setText(string);
		frame.add(label);
	}
	
	public static void mainLoop(JLabel[] label) {
		String rainbow;
		while(true) {
			for (int x = 0; x < 30; x++) {
				if (backup[x] != "") {
					String a = getConsoleLine(label, x);
					rainbow = rainbowfy(a);
					label[x].setText(rainbow);
				}
			}
			try {
				Thread.sleep(10);
			} catch(InterruptedException ex) {
				Thread.currentThread().interrupt();
			}
		}
	}
	
	public static void initConsole(JLabel[] label) {
		for (int x = 0; x < 30; x++) {
			String str = "";
			label[x] = new JLabel(str);
		}
		setConsoleLine(label, 0, "Console++ pra usar com essa linguagem chata");
		setConsoleLine(label, 1, "Versao seilaquanto");
	}
	
}
