def askQuestion(type: str, questionString: str, options: dict = {}):
    """Print a question and return the answer. The type and required options are specified in the parameters. If the answer is invalid, the question will be asked again.

    Args:
        type (str): The type of the answer. Can be 'bool', 'int', or 'string'.
        questionString (str): Question to ask.
        options (dict, optional): Parameters to specify the answer. Defaults to None.
        Parameters can be 'allowEmpty' (bool), 'Min' or 'Max'

    Returns:
        _type_: str
    """

    print(questionString)

    answer = input("> ")

    if type == 'string':
        isError = False

        if 'allowEmpty' in options and options['allowEmpty'] == False and answer == "":
            print("Empty answer is not allowed")
            isError = True
        if 'Max' in options and len(answer) > options['Max']:
            print("Answer needs to be shorter, MAND!")
            isError = True
    
    elif type == 'bool':
        isError = False

        if (answer not in [
            'y', 'Y', 'yes', 'ja',  'j', 'true',  'True',  'TRUE',
            'n', 'N', 'no',  'nee', 'n', 'false', 'False', 'FALSE'            
        ]):
            print("Please enter a valid option")
            isError = True
        
        answer = answer in ['y', 'Y', 'yes', 'ja',  'j', 'true',  'True',  'TRUE']
    
    elif type == 'int':
        isError = False
        try:
            answer = int(answer)
            if 'Min' in options and answer < options['Min']:
                print(f'Answer must be at least {options["Min"]}')
                isError = True
                raise ValueError
            if 'Max' in options and answer > options['Max']:
                print(f'Answer can be max {options["Max"]}') 
                isError = True
                raise ValueError
            if 'Choices' in options and answer not in options['Choices']:
                isError = True
                raise ValueError
        except ValueError:
            print("Unvalid answer")
            isError = True


    if isError:
        #print("\n")
        return askQuestion(type, questionString, options)

    return answer

if __name__ == '__main__':
    print("Running the 'askQuestion.py' file directly is not supported. Please run the '_main.py' file instead.")
else:
    print("askQuestion.py module is imported")

