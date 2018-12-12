#include <stdio.h>
#include <math.h>


void field(int px, int py) {

	FILE* fp;
	fp = fopen("angry.svg", "w");
	if (fp != NULL) printf("\nFile opened for writing!\n");
	else perror("ERROR: File could not be opened!");

	//Frame
	fprintf(fp, "<svg width=\"1200\" height=\"400\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
	fprintf(fp, "<line x1=\"0\" x2=\"1200\" y1=\"0\" y2=\"0\" stroke=\"black\" stroke-width=\"5\" />\n");
	fprintf(fp, "<line x1=\"0\" x2=\"1200\" y1=\"400\" y2=\"400\" stroke=\"black\" stroke-width=\"5\" />\n");
	fprintf(fp, "<line x1=\"0\" x2=\"0\" y1=\"0\" y2=\"400\" stroke=\"black\" stroke-width=\"5\" />\n");
	fprintf(fp, "<line x1=\"1200\" x2=\"1200\" y1=\"0\" y2=\"400\" stroke=\"black\" stroke-width=\"5\" />\n");

	//Mask
	fprintf(fp, "<defs>\n");
	fprintf(fp, "<linearGradient id=\"Gradient\">\n");
	fprintf(fp, "<stop offset=\"0\" stop-color=\"white\" stop-opacity=\"0\" />\n");
	fprintf(fp, " <stop offset=\"1\" stop-color=\"white\" stop-opacity=\"1\" />\n");
	fprintf(fp, "</linearGradient>\n");
	fprintf(fp, "<mask id=\"Mask\">\n");
	fprintf(fp, "<rect x=\"0\" y=\"0\" width=\"1200\" height=\"400\" fill=\"url(#Gradient)\"  />\n");
	fprintf(fp, "</mask>\n");
	fprintf(fp, "</defs>\n");
	fprintf(fp, "<rect x=\"0\" y=\"0\" width=\"1200\" height=\"400\" fill=\"green\" />\n");
	fprintf(fp, "<rect x=\"0\" y=\"0\" width=\"1200\" height=\"400\" fill=\"red\" mask=\"url(#Mask)\" />\n");

	//Text
	fprintf(fp, "<text x=\"12\" y=\"380\">Angry Birds</text>\n"); 
	fprintf(fp, "<text x=\"110\" y=\"380\">Bad Piggies</text>\n"); 


	//Bird
	fprintf(fp, "<circle cx=\"100\" cy=\"300\" r=\"10\" stroke=\"black\" fill=\"red\" stroke-width=\"3\" />\n");
	fprintf(fp, "<line x1=\"80\" x2=\"100\" y1=\"290\" y2=\"340\" stroke=\"orange\" stroke-width=\"5\" />\n");
	fprintf(fp, "<line x1=\"120\" x2=\"100\" y1=\"290\" y2=\"340\" stroke=\"orange\" stroke-width=\"5\" />\n");
	fprintf(fp, "<line x1=\"100\" x2=\"100\" y1=\"340\" y2=\"395\" stroke=\"orange\" stroke-width=\"5\" />\n");

	//Pig
	fprintf(fp, "<circle cx=\"%d\" cy=\"%d\" r=\"10\" stroke=\"black\" fill=\"green\" stroke-width=\"3\" />\n",px,py);
	fprintf(fp, "<rect x=\"%d\" y=\"%d\" width=\"40\" height=\"10\" stroke=\"black\" fill=\"gray\" stroke-width=\"3\"/>\n",(px-20),(py+10));
	fprintf(fp, "<rect x=\"%d\" y=\"%d\" width=\"10\" height=\"%d\" stroke=\"black\" fill=\"gray\" stroke-width=\"3\"/>\n",(px-5),(py+20),(400-py));

	fclose(fp);
}

void trajectory(int px, int py) {

	//Declaration
	double degree, speed, time;
	double degree_rad, x, y;
	double g = 9.81;
	int hit = 1;

	//Coordinate transform
	//Bird was on (100,300) -> now its (0,100); Therefore:
	px = px - 100;
	py = 400 - py;


	//20px/m conversion!
	px = (int) px / 20;
	py = (int) py / 20;
	/*printf("\nPX: %d PY: %d -- (Coordinates are now transformed!)", px, py);*/

	  
		for (degree = 10; degree <= 60; degree = degree + 5) {
			for (speed = 10; speed <= 30; speed++) {
				for (time = 0; time <= 10; time = time + 0.025) { //10 seconds will be more than enough!

				degree_rad = degree*3.141593 / 180;
				x = speed*time*cos(degree_rad);
				y = 5 + (speed*time*sin(degree_rad) - g / 2 * time*time); //+5 because of starting point 100px/(20px/m) -> 5m.

				if ((py < y) && (y < py + 0.5) && (px < x) && (x <= px + 0.5)) { //Pig's environment
					printf("\n%d hit! Degree: %lf, Speed: %lf",hit, degree,speed);
					hit++;

					for (time = 0; time <= 10; time = time + 0.025) {

						degree_rad = degree*3.141593 / 180;
						x = speed*time*cos(degree_rad);
						y = 5 + (speed*time*sin(degree_rad) - g / 2 * time*time); //+5 because of starting point 100px/(20px/m) -> 5m.

						FILE* fp;
						fp = fopen("angry.svg", "a");
						if (fp == NULL) printf("ERROR: File could not be opened!");

						fprintf(fp, "<circle cx=\"%d\" cy=\"%d\" r=\"2\" stroke=\"black\" fill=\"yellow\" stroke-width=\"1\" />\n", (int)(x * 20 + 100), (int)(400 - (y * 20))); //20px/m conversion
						fclose(fp);
					}
				}
			}
		}
	}
	FILE* fp;
	fp = fopen("angry.svg", "a");
	if (fp == NULL) printf("ERROR: File could not be opened!");
	fprintf(fp, "</svg>");
	fclose(fp);
	printf("\n\nWriting finished, file closed!");
}

int main(int argc, char *argv[]) {

	/*Declaration*/
	int px = 750; //px = pig_x
	int py = 250; //py = pig_y

	
	/*Input-For not only fix position this must be uncommented*/
	printf("Welcome!\n");
	/*printf("PigPosition X:[min:400 - max:1180] --- Y:[min:10 - max:300] -- (Coordinates are based on SVG format)\n");
	printf("\nExample: \n750\n250\n");
	printf("Please give the X coordinate of the pig! \n");
	scanf("%d", &px);
	printf("Please give the Y coordinate of the pig! \n");
	scanf("%d", &py);*/


	/*Functions*/
	field(px,py);
	trajectory(px,py);

	getchar();
	getchar();
	return 0;
}