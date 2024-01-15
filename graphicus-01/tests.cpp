/********
 * Fichier: tests.cpp
 * Auteurs: C.-A. Brunet
 * Date: 08 janvier 2018 (creation)
 * Description: Implementation des methodes des classes decrites dans
 *    tests.h.  Ce fichier peut etre adapte a vos besoins de tests. 
 *    Ce fichier fait partie de la distribution de Graphicus.
********/

#include "tests.h"
#include "cercle.h"
#include "rectangle.h"
#include "carree.h"
#include "couche.h"
#include <iostream>

void Tests::tests_unitaires_formes()
{
	Rectangle rectangle;
	rectangle.setWidth(12);
	rectangle.setLength(8);
	rectangle.translater(8, 6);
	rectangle.afficher(std::cout);

	Carree carree;
	carree.setCote(12);
	carree.translater(8, 2);
	carree.afficher(std::cout);

	Cercle cercle;
	cercle.setRayon(12);
	cercle.translater(8, 2);
	cercle.afficher(std::cout);
}


void Tests::tests_unitaires_vecteur()
{
	inserted_shape_returns_the_right_shape();

	test_insert_when_at_max_capacity_should_double_size_and_insert_item();

	test_insert_when_inserting_same_pointer_twice_should_refuse_to_insert_it();

	test_doubleSize_should_keep_elements();

	test_destroy_should_reset_size_and_capacity_values();

	test_deleteElement_should_return_pointer_of_deleted_element();
}

void Tests::tests_unitaires_couche()
{
	test_all_functions_should_refuse_to_execute_if_couche_is_not_active();

	test_getArea_should_return_total_area_of_all_the_shapes();
}

void Tests::tests_unitaires_canevas()
{
   // Tests sur la classe Canevas
}

void Tests::tests_unitaires()
{
   // Fait tous les tests unitaires
   tests_unitaires_formes();
   tests_unitaires_vecteur();
   tests_unitaires_couche();
   tests_unitaires_canevas();
}

void Tests::tests_application()
{
   // Fait tous les tests applicatifs
   tests_application_cas_01();
   tests_application_cas_02();
}

void Tests::tests_application_cas_01()
{
   cout << "TESTS APPLICATION (CAS 01)" << endl; 
   // Il faut ajouter les operations realisant ce scenario de test.
}

void Tests::tests_application_cas_02()
{
   cout << "TESTS APPLICATION (CAS 02)" << endl;  
    // Il faut ajouter les operations realisant ce scenario de test.
}

//*******************************Tests sur les vecteur**********************************************//
void inserted_shape_returns_the_right_shape()
{
	Vecteur testVecteur;
	
	Cercle *cercle1 = new Cercle(10, 5, 5);

	if(testVecteur.insert(cercle1))
	{
		Cercle *result = (Cercle*)testVecteur.getShape(0);
		if (result->getRayon() == 10)
		{
			std::cout << "Success" << endl;
		}
		else
		{
			std::cout << "Fail: Expected Rayon to be 10 but was " << result->getRayon() << endl;
		}
	}

	delete cercle1;
	
}

void test_insert_when_at_max_capacity_should_double_size_and_insert_item()  
{
	Vecteur testVecteur;

	int number_of_loops = testVecteur.capacity() + 1;

	int initialCapacity = testVecteur.capacity();

	for(int i = 0; i < number_of_loops; i++)
	{
		testVecteur.insert(new Cercle);
	}

	if(testVecteur.size() == number_of_loops && testVecteur.capacity() == initialCapacity * 2)
	{
		cout << "Success" << endl;
	}
	else
	{
		cout << "Fail" << endl;
		cout << "Expected size: " << number_of_loops << " Actual: " << testVecteur.size() << endl;
		cout << "Expected capacity: " << initialCapacity * 2 << " Actual: " << testVecteur.capacity() << endl;
	}

	testVecteur.destroy();
}

void test_insert_when_inserting_same_pointer_twice_should_refuse_to_insert_it()
{
	Vecteur testVecteur;

	Cercle *cercle1 = new Cercle;

	testVecteur.insert(cercle1);
	if(testVecteur.insert(cercle1))
	{
		cout << "Fail: Wasn't supposed to accept the same pointer" << endl;
	}
	else
	{
		cout << "Success" << endl;
	}
}

void test_destroy_should_reset_size_and_capacity_values()
{
	Vecteur testVecteur;

	int numberOfLoops = 15;

	for(int i = 0; i < numberOfLoops; i++)
	{
		Cercle *cercle = new Cercle(3, 5, 7);
		testVecteur.insert(cercle);
	}

	testVecteur.destroy();

	if(testVecteur.capacity() == 2 && testVecteur.size() == 0)
	{
		cout << "Success" << endl;
	}
	else
	{
		cout << "Fail: (Expected capacity: 2 Actual: " << testVecteur.capacity() << ") (Expected size: 0 Actual: " << testVecteur.size() << ")" << endl;
	}
}

void test_doubleSize_should_keep_elements()
{
	Vecteur testVecteur;

	int numberOfLoops = testVecteur.capacity();

	Forme* *formesBeforeDoubleSize = new Forme*[numberOfLoops]; 

	for(int i = 0; i < numberOfLoops; i++)
	{
		Cercle *cercle = new Cercle;
		testVecteur.insert(cercle);	
		formesBeforeDoubleSize[i] = cercle;
	}

	testVecteur.doubleSize();

	for(int i = 0; i < numberOfLoops; i++)
	{
		if(testVecteur.getShape(i) != formesBeforeDoubleSize[i])
		{
			cout << "Fail: pointers are different" << endl;
			return;
		}
	}

	cout << "Success" << endl;
	return;
}

void test_deleteElement_should_return_pointer_of_deleted_element() //I think it works, but I don't know how to test it
{
	Vecteur testVecteur;

	Cercle *cercle = new Cercle(3, 4, 5);

	testVecteur.insert(cercle);

	Forme* deletedForme = cercle;

	//cout << "deletedForme " << deletedForme << endl;
	//cout << "deletedElement" << testVecteur.deleteElement(0) << endl;

	testVecteur.deleteElement(0);

	cout << deletedForme->getAncrage().x << endl; 

	cout << (testVecteur.getShape(0))->getAncrage().x << endl; 

	//if((testVecteur.getShape(0))->getAncrage().x == deletedForme->getAncrage().x)
	//{
	//	cout << "Fail" << endl;		
	//	return;
	//}

	//cout << "Success" << endl;

	return;
}

/********************Tests sur les couches********************/
void test_all_functions_should_refuse_to_execute_if_couche_is_not_active()
{
	Couche couche;

	Cercle *cercle = new Cercle;

	if(couche.addShape(cercle) == false)
	{
		cout << "Success" << endl;
	}
	if(couche.getArea() == 0)
	{
		cout << "Success" << endl;
	}
	if(couche.translaterFormes(3, 5) == false)
	{
		cout << "Success" << endl;
	}


	couche.print(std::cout);

	delete cercle;
}

void test_getArea_should_return_total_area_of_all_the_shapes()
{
	Couche couche;

	couche.changeState(1);

	int rectangleLength = 1;
	int rectangleWidth = 1;

	int circleRadius = 1;

	int squareSide = 1;

	Rectangle *rectangle = new Rectangle(rectangleLength, rectangleWidth, 0, 0); 
	Cercle *cercle = new Cercle(circleRadius, 0, 0); 
	Carree *carree = new Carree(squareSide, 0, 0); 

	couche.addShape(rectangle);
	couche.addShape(cercle);
	couche.addShape(carree);

cout << ((M_PI * circleRadius * circleRadius) + (rectangleLength * rectangleLength) + (squareSide * squareSide)) << endl;

	cout << couche.getArea() << endl;

	delete cercle;
	delete carree;
	delete rectangle;
}





