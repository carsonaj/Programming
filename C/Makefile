
#Declaring some variables i will use later in the form of $(var)
Make=make
TESTDIRECTORY=LibTests

#if user wants to make all he will enter make all also because this is the 
#first one if the user just enters make this will run
all: #if we wanted we can add tests to be made  
	#call make all ($@ = target = all)
	$(Make) $@


tests:
	#call make in the TestsDirectory there should be instructions to make there	
	$(Make) $@ -C $(TESTDIRECTORY)

clean:
	cd $(TESTDIRECTORY) && $(Make) clean

