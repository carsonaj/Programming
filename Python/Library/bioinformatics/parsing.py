def parse_fasta(file):
    label, sequence = None, []
    for line in file:
        line = line.rstrip()
        if line.startswith('>'):
            if label:
                yield (label, ''.join(sequence))
            label, sequence = line[1:], []
        else:
            sequence.append(line)
    yield (label, ''.join(sequence))
