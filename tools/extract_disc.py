#!/usr/bin/env python3
"""Copy what the game plays from its CD into the game directory: the herald
and movie videos (KINGS\\, VIDEO\\ of the data track) and the music (the
CD's audio tracks, as Music\\TrackNN.wav: track N of the disc).

    python3 tools/extract_disc.py DISC GAMEDIR

DISC is the disc image: a .cue (with its .bin, raw 2352-byte sectors, data
track first), or a .zip holding them.  GAMEDIR is the installed game
(default ~/Civ2).  Needs no other tools; a zip is unpacked to a temporary
directory first (about 700 MB).
"""
import os
import re
import shutil
import struct
import sys
import tempfile
import zipfile

SECTOR = 2352


def parse_cue(path):
    """[(track, mode, start sector of INDEX 01)] and the .bin file name."""
    tracks, binfile, cur = [], None, None
    for line in open(path, errors='replace'):
        w = line.split()
        if not w:
            continue
        if w[0] == 'FILE':
            binfile = re.search(r'"([^"]+)"', line).group(1) if '"' in line else w[1]
        elif w[0] == 'TRACK':
            cur = [int(w[1]), w[2], None]
            tracks.append(cur)
        elif w[0] == 'INDEX' and w[1] == '01':
            m, s, f = (int(x) for x in w[2].split(':'))
            cur[2] = (m * 60 + s) * 75 + f
    return tracks, binfile


class Iso:
    """ISO 9660 file system of the data track (MODE1/2352: user data at 16)."""

    def __init__(self, f, start):
        self.f, self.start = f, start

    def read(self, sector, n=1):
        out = b''
        for i in range(n):
            self.f.seek((self.start + sector + i) * SECTOR + 16)
            out += self.f.read(2048)
        return out

    def entries(self, extent, size):
        data = self.read(extent, (size + 2047) // 2048)
        i = 0
        while i < size:
            ln = data[i]
            if ln == 0:
                i = (i // 2048 + 1) * 2048
                continue
            rec = data[i:i + ln]
            i += ln
            name = rec[33:33 + rec[32]]
            if name in (b'\0', b'\1'):
                continue
            yield (name.decode('latin1').split(';')[0], struct.unpack('<I', rec[2:6])[0],
                   struct.unpack('<I', rec[10:14])[0], bool(rec[25] & 2))

    def walk(self, extent=None, size=None, path=''):
        if extent is None:
            root = self.read(16)[156:156 + 34]
            extent, size = struct.unpack('<I', root[2:6])[0], struct.unpack('<I', root[10:14])[0]
        for name, ext, sz, d in self.entries(extent, size):
            p = path + '/' + name
            if d:
                yield from self.walk(ext, sz, p)
            else:
                yield p, ext, sz

    def extract(self, extent, size, dst):
        with open(dst, 'wb') as out:
            done = 0
            while done < size:
                n = min(64, (size - done + 2047) // 2048)
                chunk = self.read(extent + done // 2048, n)
                out.write(chunk[:size - done])
                done += len(chunk)


def wav(dst, f, first, count):
    """Raw CD audio sectors (44.1 kHz, 16-bit stereo, little-endian) as a WAV file."""
    n = count * SECTOR
    with open(dst, 'wb') as out:
        out.write(b'RIFF' + struct.pack('<I', 36 + n) + b'WAVEfmt ' +
                  struct.pack('<IHHIIHH', 16, 1, 2, 44100, 44100 * 4, 4, 16) + b'data' + struct.pack('<I', n))
        f.seek(first * SECTOR)
        left = n
        while left:
            b = f.read(min(left, 1 << 20))
            if not b:
                break
            out.write(b)
            left -= len(b)


def subdir(game, name):
    """game/name, or the directory already there under another case."""
    for d in os.listdir(game):
        if d.lower() == name.lower() and os.path.isdir(os.path.join(game, d)):
            return os.path.join(game, d)
    os.makedirs(os.path.join(game, name), exist_ok=True)
    return os.path.join(game, name)


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    disc = sys.argv[1]
    game = os.path.expanduser(sys.argv[2] if len(sys.argv) > 2 else '~/Civ2')
    if not os.path.isdir(game):
        sys.exit('%s: no such directory' % game)
    tmp = None
    if disc.lower().endswith('.zip'):
        tmp = tempfile.mkdtemp(prefix='civ2disc')
        with zipfile.ZipFile(disc) as z:
            for m in z.namelist():
                if m.lower().endswith(('.cue', '.bin')):
                    print('unpacking', m)
                    with z.open(m) as src, open(os.path.join(tmp, os.path.basename(m)), 'wb') as dst:
                        shutil.copyfileobj(src, dst, 1 << 20)
        cues = [x for x in os.listdir(tmp) if x.lower().endswith('.cue')]
        if not cues:
            sys.exit('no .cue file in %s' % disc)
        disc = os.path.join(tmp, cues[0])
    try:
        tracks, binfile = parse_cue(disc)
        binpath = os.path.join(os.path.dirname(disc), binfile)
        size = os.path.getsize(binpath) // SECTOR
        with open(binpath, 'rb') as f:
            data = [t for t in tracks if t[1].startswith('MODE1')]
            if data:
                iso = Iso(f, data[0][2])
                for p, ext, sz in iso.walk():
                    parts = p.strip('/').split('/')
                    if len(parts) == 3 and parts[0].upper() == 'CIV2' and parts[1].upper() in ('KINGS', 'VIDEO'):
                        d = subdir(game, parts[1].upper())
                        iso.extract(ext, sz, os.path.join(d, parts[2].upper()))
                        print('%s/%s' % (parts[1].upper(), parts[2].upper()))
            audio = [t for t in tracks if t[1] == 'AUDIO']
            music = subdir(game, 'Music') if audio else None
            starts = [t[2] for t in tracks] + [size]
            for i, t in enumerate(tracks):
                if t[1] != 'AUDIO':
                    continue
                dst = os.path.join(music, 'Track%02d.wav' % t[0])
                wav(dst, f, t[2], starts[i + 1] - t[2])
                print('Music/Track%02d.wav' % t[0])
    finally:
        if tmp:
            shutil.rmtree(tmp)


if __name__ == '__main__':
    main()
