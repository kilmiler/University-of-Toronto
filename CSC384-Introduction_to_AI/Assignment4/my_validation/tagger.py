# The tagger.py starter code for CSC384 A4.
# Currently reads in the names of the training files, test file and output file,
# and calls the tagger (which you need to implement)
import os
import sys
import numpy as np


all_tags = ["AJ0", "AJC", "AJS", "AT0", "AV0", "AVP", "AVQ", "CJC", "CJS", "CJT", "CRD", 
            "DPS", "DT0", "DTQ", "EX0", "ITJ", "NN0", "NN1", "NN2", "NP0", "ORD", 
            "PNI", "PNP", "PNQ", "PNX", "POS", "PRF", "PRP", "PUL", "PUN", "PUQ", "PUR", 
            "TO0", "UNC", 
            "VBB", "VBD", "VBG", "VBI", "VBN", "VBZ", "VDB", "VDD", "VDG", 
            "VDI", "VDN", "VDZ", "VHB", "VHD", "VHG", "VHI", "VHN", "VHZ", 
            "VM0", "VVB", "VVD", "VVG", "VVI", "VVN", "VVZ", "XX0", "ZZ0", 
            "AJ0-AV0", "AJ0-VVN", "AJ0-VVD", "AJ0-NN1", "AJ0-VVG", "AVP-PRP", "AVQ-CJS", 
            "CJS-PRP", "CJT-DT0", "CRD-PNI", 
            "NN1-NP0", "NN1-VVB", "NN1-VVG", "NN2-VVZ", "VVD-VVN"]

all_probs = {
    tag: { # S
        "initialProb": 0, # Initial Probability P(S0)
        "transitionProb": { # Transition Probability P(S|S-1) 
            # Prob of having tag_t after tag
            # For EACH Tag
            # S-1: tag -> S: tag_t
            tag_t: 0 for tag_t in all_tags 
        }, 
        "emissionProb": { # Emission Proboability P(E|S)
            # Prob of having word for that tag
            # S -> E
            # For EACH Word (Create the Word here if it appears for the Tag)
        }
    } for tag in all_tags
}


# E: test words. S: all tags. I: initial probabilities. T: transition matrix. M: emission matrix.
def Viterbi(E, S):
    # I: all_probs[tag]["initialProb"]
    # T: all_probs[tag]["transitionProb"][tag_t]
    # M: all_probs[tag]["emissionProb"][word]
    prob = np.zeros( (len(E), len(S)) )
    prev = np.zeros( (len(E), len(S)) )
    
    # Determine values for time step 0 
    for i in range(len(S)):
        if(E[0] in all_probs[all_tags[i]]["emissionProb"]):
            prob[0][i] = all_probs[all_tags[i]]["initialProb"] * all_probs[all_tags[i]]["emissionProb"][E[0]]
        else:
            prob[0][i] = 0

        prev[0][i] = None
    
    if(not np.any(prob[0])): #IF word is not part of EmissionProb for All Tags
            prob[0][3] = 1 #3 - AT0 BEST (35835) (82%)

    # Normalizing
    sum_probs = 0
    for i in prob[0]:
        sum_probs += i
    for i in range(len(S)-1): 
        if prob[0][i] != 0:
            prob[0][i] = prob[0][i]/sum_probs

    # For time steps 1 to length(E)-1,
    # find each current state's most likely prior state x. 
    for t in range(1, len(E)):
        for i in range(len(S)):
            prob_index = []
            for x in range(len(S)):
                if(E[t] in all_probs[all_tags[i]]["emissionProb"]):
                    prob_index.append(prob[t-1][x] * all_probs[all_tags[x]]["transitionProb"][all_tags[i]] * all_probs[all_tags[i]]["emissionProb"][E[t]])
                else:
                    prob_index.append(0)

            x = np.argmax(prob_index)

            if(E[t] in all_probs[all_tags[i]]["emissionProb"]):
                prob[t][i] = prob[t-1][x] * all_probs[all_tags[x]]["transitionProb"][all_tags[i]] * all_probs[all_tags[i]]["emissionProb"][E[t]]
            else:
                prob[t][i] = 0
               
            prev[t][i] = x

        if(not np.any(prob[t])): #IF word is not part of EmissionProb for All Tags
            prob[t][17] = 1 #17 - NN1 BEST (35835) (82%)

        # Normalizing
        sum_probs = 0
        for i in prob[t]:
            sum_probs += i
        for i in range(len(S)-1): 
            if prob[t][i] != 0:
                prob[t][i] = prob[t][i]/sum_probs

    return prob, prev


def ambig_tags(tag):
    if tag in all_tags: #If tag Exists in all_tags List, just Return the tag
        return tag
    else: #If tag Does Not Exist in all_tags List, it means the ambigious tag is Flipped
        tag_r = tag[:tag.find("-")]
        tag_l = tag[tag.find("-")+1:]
        tag = tag_l + "-" + tag_r
        return tag


def calc_initialProbs(training_Data): # P(S0)
    prev_word = ''
    prev_prev_word = ''
    PUQ_counter = 0
    sentence_counter = 0

    # For Each Word-Tag Pair
    for pair in training_Data:
        word = pair[:pair.rfind(":")-1]
        tag = pair[pair.rfind(":")+2:-1]
        tag = ambig_tags(tag)
        
        # Just my own thought.. could be wrong
        # 6 Correct Possibilities (with . , ! , ? but only . shown):
        #1# Sentence.
        #2# "Sentence." 
        #3# Sentence. Sentence.
        #4# "Sentence." Sentence.
        #5# Sentence. "Sentence". 
        #6# "Sentence." "Sentence". 

        if (word == '"'):
            #   Case2,6         or Case4,5          or Case4,5          or Case4,5          or Case6            or in the middle of sentence
            if (prev_word == '' or prev_word == '.' or prev_word == '!' or prev_word == '?' or prev_word == '"' or prev_word == ',' or prev_word == '-'): 
                # Corner cases where <"> was used instead of <'> by error  # e.g. we " ll do something
                PUQ_counter += 1 # Counting PUQs <"> to know when Quotation Opens and Closed
        else:            
            if ((prev_word == '' or prev_word == '.' or prev_word == '!' or prev_word == '?') and word[0].isupper() == True):
                all_probs[tag]["initialProb"] += 1
                sentence_counter += 1
            elif (prev_word == '"' and (prev_prev_word == '' or prev_prev_word == '.' or prev_prev_word == '!' or prev_prev_word == '?' or prev_prev_word == '"') and word[0].isupper() == True):
                if (PUQ_counter % 2 == 1): # Quotation Open
                    all_probs['PUQ']["initialProb"] += 1
                    sentence_counter += 1
                elif (PUQ_counter % 2 == 0): # Quotation Closed
                    all_probs[tag]["initialProb"] += 1
                    sentence_counter += 1
        
        prev_prev_word = prev_word
        prev_word = word

    # Normalizing
    for tag in all_tags:
        all_probs[tag]["initialProb"] = all_probs[tag]["initialProb"]/sentence_counter
    

def calc_transitionProbs(training_Data): # P(S|S-1)
    prev_tag = ''

    for pair in training_Data:
        tag_t = pair[pair.rfind(":")+2:-1]
        tag_t = ambig_tags(tag_t)

        if (prev_tag != ''):
            all_probs[prev_tag]["transitionProb"][tag_t] += 1

        prev_tag = tag_t

    # Normalizing
    for tag in all_tags: # tag comes before tag_t P(tag -> tag_t)
        sum_of_tag_t_for_tag = 0

        for tag_t in all_tags:
            sum_of_tag_t_for_tag += all_probs[tag]["transitionProb"][tag_t]

        for tag_t in all_tags:
            all_probs[tag]["transitionProb"][tag_t] = all_probs[tag]["transitionProb"][tag_t]/sum_of_tag_t_for_tag


def calc_emissionProbs(training_Data): # P(E|S)
    for pair in training_Data:
        word = pair[:pair.rfind(":")-1]
        tag = pair[pair.rfind(":")+2:-1]
        tag = ambig_tags(tag)

        if word not in all_probs[tag]["emissionProb"]:
            all_probs[tag]["emissionProb"][word] = 1
        else:
            all_probs[tag]["emissionProb"][word] += 1
            
    # Normalizing
    for tag in all_tags:
        sum_of_words_for_tag = 0

        for word in all_probs[tag]["emissionProb"]:
            sum_of_words_for_tag += all_probs[tag]["emissionProb"][word]

        for word in all_probs[tag]["emissionProb"]:
            all_probs[tag]["emissionProb"][word] = all_probs[tag]["emissionProb"][word]/sum_of_words_for_tag


def read_Training_List(training_list):
    training_Data = [] # Contains the Entire Training Data (Array of Strings)

    # Only One Training File Given (e.g. ["training1.txt"])
    # OR
    # More Than Two Training Files Given (e.g. ["training1.txt", "training2.txt"])
    for i in range(len(training_list)):
        f = open(training_list[i], 'r')
        input = f.readlines()
        training_Data.extend(input)
        f.close()
        
    return training_Data


def read_Testing_File(test_file):
    # Only One Test File Given (e.g. "test1.txt"])
    test_Data = [] # Contains the Entire Test Data (Array of Strings)

    f = open(test_file, 'r')
    input = f.readlines()
    f.close()

    for word in input:
        word = word[:word.find("\n")]
        test_Data.append(word)

    return test_Data


def make_Output_File(test_Data, output_file, prob):
    f = open(output_file, 'w')
    for word in range(len(test_Data)):
        one_line = test_Data[word] + " : " + all_tags[np.argmax(prob[word])] + "\n"
        f.write(one_line)
    f.close()
    

def tag(training_list, test_file, output_file):
    # Tag the words from the untagged input file and write them into the output file.
    # Doesn't do much else beyond that yet.
    print("Tagging the file.")
    #
    # YOUR IMPLEMENTATION GOES HERE
    #

    # Training
    training_Data = read_Training_List(training_list)
    calc_initialProbs(training_Data)
    calc_transitionProbs(training_Data)
    calc_emissionProbs(training_Data)

    # Reading Test File
    test_Data = read_Testing_File(test_file)
    
    # Tagging using Viterbi
    prob = np.zeros( (len(test_Data), len(all_tags)) )
    prev = np.zeros( (len(test_Data), len(all_tags)) )
    prob, prev = Viterbi(test_Data, all_tags) # E: Words. S: Tags. I: initial probabilities. T: transition matrix. M: emission matrix.

    # Using the Viterbi Probability to output Tags to output_file
    make_Output_File(test_Data, output_file, prob)

    
if __name__ == '__main__':
    # Run the tagger function.
    print("Starting the tagging process.")

    # Tagger expects the input call: "python3 tagger.py -d <training files> -t <test file> -o <output file>"
    parameters = sys.argv
    training_list = parameters[parameters.index("-d")+1:parameters.index("-t")]
    test_file = parameters[parameters.index("-t")+1]
    output_file = parameters[parameters.index("-o")+1]
    print("Training files: " + str(training_list))
    print("Test file: " + test_file)
    print("Output file: " + output_file)

    # Start the training and tagging operation.
    tag (training_list, test_file, output_file)