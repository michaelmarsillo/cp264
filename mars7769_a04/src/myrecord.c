/*
--------------------------------------------------
Project: a4q2
File:    myrecord.c
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "myrecord.h"
#include "mysort.h"


int cmp1(void *x, void *y) {
	float scoreA = ((RECORD*) x)->score;
	float scoreB = ((RECORD*) y)->score;
	return (scoreB > scoreA) - (scoreB < scoreA); // Flip the comparison for descending order
}

/*
 * Convert a percentage grade to letter grade defined by percentage ranges
 * A+=[90, 100], A=[85, 90), A-=[80, 85), B+=[77, 80), B=[73, 77) B=[70, 73),
 * C+=[67, 70), C=[63, 77), C-=[60, 63), D+=[57,60),D=[53,57),D=[50,53), F=[0,50).
 *
 * @param score -  percetage grade.
 *
 * @return - letter grade wrapped in GRADE structure type.
 */

GRADE grade(float score){
   GRADE r = {"F"};
   // your code
   if (score >= 90) return (GRADE){ "A+"};
   else if (score >= 85) return (GRADE){ "A"};
   else if (score >= 80) return (GRADE){ "A-"};
   else if (score >= 77) return (GRADE){ "B+"};
   else if (score >= 73) return (GRADE){ "B"};
   else if (score >= 70) return (GRADE){ "B-"};
   else if (score >= 67) return (GRADE){ "C+"};
   else if (score >= 63) return (GRADE){ "C"};
   else if (score >= 60) return (GRADE){ "C-"};
   else if (score >= 57) return (GRADE){ "D+"};
   else if (score >= 53) return (GRADE){ "D"};
   else if (score >= 50) return (GRADE){ "D-"};
   else return (GRADE){"F"};

   return r;
}


/*
 *  Import record data from file and store name and store all record entries
 *  in the RECORD array passed by records, return the number of record count.
 *
 *  @param *fp -  FILE pointer to intput file.
 *  @param dataset - array of RECODR type to store record data.
 *  @return   - number of records
 */

int import_data(FILE *fp, RECORD *dataset) {
// your code
	char line[1000];

		int i = 0;
		while (fgets(line, sizeof(line), fp) != NULL) {
			sscanf(line, "%[^,], %f", dataset[i].name, &dataset[i].score);
			i++;
		}
		return i;

}


/*
 *  Take the RECORD data array as input, compute the average score, standard deviation,
 *  median of the score values of the record data, and returns the STATS type value.
 *
 *  @param dataset -  input record data array.
 *  @param count -  the number of data record in dataset array.
 *  @return  -  stats value in STATS type.
 */

STATS process_data(RECORD *dataset, int count) {
// your code
	STATS stats = { count, 0.0, 0.0, 0.0 };

		//average
		float sum = 0.0;
		for (int i = 0; i < count; i++) {
			sum += dataset[i].score;

		}

		stats.mean = sum / count;

		//mean
		float variance_sum = 0.0;
		for (int i = 0; i < count; i++) {
			variance_sum += (dataset[i].score - stats.mean)
					* (dataset[i].score - stats.mean);

		}

		stats.stddev = sqrt(variance_sum / count);

		//median
		void *ptrs[count];
		for (int i = 0; i < count; i++) {
			ptrs[i] = &dataset[i];
		}

		my_sort(ptrs, 0, count - 1, cmp1);
		if (count % 2 == 1) {
			stats.median = ((RECORD*) ptrs[count / 2])->score;
		} else {
			float mid1 = ((RECORD*) ptrs[count / 2 - 1])->score;
			float mid2 = ((RECORD*) ptrs[count / 2])->score;
			stats.median = (mid1 + mid2) / 2.0;
		}
		return stats;

}


/*
 *  This function takes output file named outfilename, RECORD array records,
 *  and stats as inputs, prepare and write report of stats and grade to files.
 *  The records in report file are sorted in decreasing of scores.
 *
 *  @param *fp -  FILE pointer to output file.
 *  @param *dataset - pointer to dataset array.
 *  @param count - the number of data record in dataset array.
 *  @return - returns 1 if successful; 0 if count < 1
 */

int report_data(FILE *fp, RECORD *dataset, STATS stats) {
// your code

	int n = stats.count;
		if (n < 1) {
			return 0;
		}

		fprintf(fp, "Stats:value\n");
		fprintf(fp, "Count:%.2d\n", stats.count);
		fprintf(fp, "Mean:%.1f\n", stats.mean);
		fprintf(fp, "Standard Deviation:%.1f\n", stats.stddev);
		fprintf(fp, "Median:%.2f\n\n", stats.median);

		void *p[n];
		for (int i = 0; i < n; i++) {
			p[i] = &dataset[i];

		}

		my_sort(p, 0, n - 1, cmp1);
		fprintf(fp, "name:score,grade\n");

		for (int i = 0; i < n; i++) {
			RECORD *rec = (RECORD*) p[i];
			GRADE g = grade(rec->score);
			fprintf(fp, "%s:%.1f,%s\n", rec->name, rec->score, g.letter_grade);

		}
		return 1;

}
