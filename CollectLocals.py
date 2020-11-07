import os

class TSourceNode():
    def __init__(self, sourceFile):
        self._dependences = {}
        self._sourceLines = []
        self._sourceFileName = sourceFile
        self._sourceFile = open(sourceFile, "r")
        self._headers = set()

        self.__read()

    def __read(self):
        dir = self._sourceFileName[::-1].split('/', 2)[-1][::-1] + "/" if self._sourceFileName.find("/") != -1 else ""
        for line in self._sourceFile:
            if self.__isPragma(line):
                continue
            if self.__isHeader(line):
                if line.find('\"') != -1:
                    self._dependences[line] = TSourceNode( dir + self.__getDependence(line))
                else:
                    self._headers.add(line)
                continue
            self._sourceLines.append(line)

        print(self._sourceFileName)
        print("dependence: ")
        for dependence in self._dependences.keys():
            print(dependence)
        print ("headers: ")
        for header in self._headers:
            print(header)


    def __isPragma(self, line):
        return line.find("pragma") != -1

    def __isHeader(self, line):
        return line.find("include") != -1
    
    def __getDependence(self, line):
        return line.split('\"')[1]

    def __writeHeader(self, ouputFile):
        if self._sourceFileName.split('.')[-1] == 'cpp':
            return
        for line in self._sourceLines:
            ouputFile.write(line)

    def __writeCpp(self, outputFile):
        if self._sourceFileName.split('.')[-1] != 'cpp':
            return
        for line in self._sourceLines:
            outputFile.write(line)


    def HasDependences(self):
        return len(self._dependences) == 0
    
    def HashDependence(self, dependence):
        return dependence in self._dependences

    def GetDependences(self):
        depences = self._dependences.copy()
        for dependence in self._dependences.values():
            depences.update(dependence.GetDepences())
        return depences

    def GetHeaders(self):
        headers = self._headers.copy()
        for header in map(lambda x: x.GetHeaders(), self._dependences.values()):
            headers.update(header)
        return headers

    def GetFileNameFromInclude(self, include):
        return include.split('/')[-1]
    
    def WriteHeaders(self, outputFile, used):
        used.add(self.GetFileNameFromInclude(self._sourceFileName))
        for include, sourceNode in self._dependences.items():
            file = self.GetFileNameFromInclude(include)
            if file in used:
                continue
            else:
                used.add(file)
                sourceNode.WriteHeaders(outputFile, used)
        self.__writeHeader(outputFile)

    def WriteCppFiles(self, outputFile, used):
        used.add(self.GetFileNameFromInclude(self._sourceFileName))
        for include, sourceNode in self._dependences.items():
            file = self.GetFileNameFromInclude(include)
            if file in used:
                continue
            else:
                used.add(file)
                sourceNode.WriteCppFiles(outputFile, used)
        self.__writeCpp(outputFile)


def Main():
    inputFile = input("Enter inputFile: ")
    outputFile = input("Enter outputFile: ")
    outFile = open(outputFile, "w+")

    node = TSourceNode(inputFile)
    headers = node.GetHeaders()
    for header in headers:
        outFile.write(header)
    node.WriteHeaders(outFile, set())
    node.WriteCppFiles(outFile, set())


if __name__ == "__main__":
    Main()
