/* The game, text: game text files, strings, resources and files: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 0040bbb0 auto */
void __cdecl text_clear(void)

{
  str_clear(ADDR(0x679640, ((u8 *)&g.d_00679640)));
  return;
}

/* 0040bbe0 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
void __cdecl text_append(iptr param_1)

{
  FUN_005f22e0(&text_buffer,param_1);
  return;
}
#undef text_buffer

/* 0040bc10 auto */
void __cdecl text_append_label(i32 param_1)

{
  str_append_label(ADDR(0x679640, ((u8 *)&g.d_00679640)),param_1);
  return;
}

/* 0040fe10 auto */
void __cdecl text_append_space(void)

{
  str_append_space(ADDR(0x679640, ((u8 *)&g.d_00679640)));
  return;
}

/* 0040fe40 auto */
void __cdecl text_append_colon(void)

{
  str_append_colon(ADDR(0x679640, ((u8 *)&g.d_00679640)));
  return;
}

/* 0040fe70 auto */
void __cdecl text_append_percent(void)

{
  str_append_percent(ADDR(0x679640, ((u8 *)&g.d_00679640)));
  return;
}

/* 0040fea0 auto */
void __cdecl text_append_lparen(void)

{
  str_append_lparen(ADDR(0x679640, ((u8 *)&g.d_00679640)));
  return;
}

/* 0040fed0 auto */
void __cdecl text_append_rparen(void)

{
  str_append_rparen(ADDR(0x679640, ((u8 *)&g.d_00679640)));
  return;
}

/* 0040ff00 auto */
void __cdecl text_append_string_id(i32 param_1)

{
  str_append_string_id(ADDR(0x679640, ((u8 *)&g.d_00679640)),param_1);
  return;
}

/* 0040ff30 auto */
void __cdecl text_append_int(iptr param_1)

{
  str_append_int(ADDR(0x679640, ((u8 *)&g.d_00679640)),param_1);
  return;
}

/* 0040ff60 auto */
i32 __cdecl text_set_string_arg(iptr param_1,iptr param_2)

{
  i32 uVar1;
  
  uVar1 = FUN_005f22d0(&text_string_args + param_1 * 0x104,param_2);
  return uVar1;
}

/* 00414d70 auto */
void __cdecl text_append_str(iptr param_1)

{
  str_concat(ADDR(0x679640, ((u8 *)&g.d_00679640)),param_1);
  return;
}

/* 00415040 auto */
iptr __cdecl file_build_open_path(iptr param_1,i32 param_2)

{
  if (DAT_00625114 == '\0') {
    FUN_005f22d0(param_1,param_2);
  }
  else {
    path_join_upper(param_1,ADDR(0x6250d8, ((u8 *)&g.d_006250d8)),param_2);
  }
  return param_1;
}

/* 0041508c auto */
#define error_last_open_failed (*(uint *)((u8 *)&g.d_00634810))
#define local_8c (*(char (*)[136])(frame_ + FRAME_OFF(4)))
FILE * __cdecl file_open_path(iptr param_1,iptr param_2)

{
  FILE *pFVar1;
  i8 frame_[FRAME_OFF(144)] __attribute__((aligned(8)));  /* original stack frame */
  
  file_build_open_path((iptr)local_8c,param_1);
  FUN_005f22d0(&error_last_open_path,local_8c);
  pFVar1 = _fopen(local_8c,(char *)param_2);
  error_last_open_failed = (uint)(pFVar1 == (FILE *)0x0);
  return pFVar1;
}
#undef error_last_open_failed
#undef local_8c

/* 00415133 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
uint __cdecl file_exists(iptr param_1)

{
  FILE *_File;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  _File = (FILE *)file_open_path(param_1,ADDR(0x625118, ((u8 *)&g.d_00625118)));
  if (_File != (FILE *)0x0) {
    _fclose(_File);
  }
  local_8 = (uint)(_File != (FILE *)0x0);
  return local_8;
}
#undef local_8

/* 004190a0 auto */
void __cdecl text_append_spaces(i32 param_1)

{
  str_append_spaces(ADDR(0x679640, ((u8 *)&g.d_00679640)),param_1);
  return;
}

/* 0041e7e3 auto */
void __cdecl labels_reload(void)

{
  int iVar1;
  
  iVar1 = text_open_section((iptr)PTR_s_LABELS_00627674,ADDR(0x625618, ((u8 *)&g.d_00625618)));
  if (iVar1 == 0) {
    text_read_line(1);
    iVar1 = text_next_int();
    if (strpool_capacity < iVar1) {
      strpool_capacity = iVar1;
    }
  }
  strpool_init(strpool_capacity);
  strpool_add(ADDR(0x625624, ((u8 *)&g.d_00625624)));
  labels_free();
  labels_load();
  dialog_load_button_labels();
  return;
}

/* 00421bf0 auto */
/* Library Function - Multiple Matches With Same Base Name
    protected: virtual unsigned char * __thiscall CHtmlStream::Realloc(unsigned char *,unsigned
   long)
    protected: virtual unsigned char * __thiscall CMemFile::Realloc(unsigned char *,unsigned long)
   
   Library: Visual Studio 1998 Debug */

i32 __thiscall file_obj_create(FileObject *this,iptr param_1)

{
  i32 uVar1;
  
  uVar1 = file_obj_create_path(param_1,(iptr)this);
  return uVar1;
}

/* 00421c30 auto */
i32 __thiscall file_map_close(FileObject *this)

{
  i32 uVar1;
  
  uVar1 = file_obj_close_handle((iptr)this);
  return uVar1;
}

/* 00421c60 auto */
void __thiscall file_obj_write(FileObject *this,iptr param_1,i32 param_2)

{
  file_obj_write_bytes((iptr)this,param_1,param_2);
  return;
}

/* 00421d30 auto */
void __cdecl text_append_comma(void)

{
  str_append_comma(ADDR(0x679640, ((u8 *)&g.d_00679640)));
  return;
}

/* 00421d60 auto */
i32 __cdecl text_set_string_arg_b(int param_1,iptr param_2)

{
  i32 uVar1;
  
  uVar1 = FUN_005f22d0(&text_string_args + param_1 * 0x104,param_2);
  return uVar1;
}

/* 00421da0 auto */
i32 __cdecl text_set_number_arg(int param_1,i32 param_2)

{
  *(i32 *)(&text_number_args + param_1 * 4) = param_2;
  return param_2;
}

/* 00421f10 auto */
void __cdecl text_append_year(i32 param_1)

{
  str_append_year(ADDR(0x679640, ((u8 *)&g.d_00679640)),param_1);
  return;
}

/* 00426ff0 auto */
#define local_34 (*(char * *)(frame_ + FRAME_OFF(4)))
#define local_30 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_2c (*(char (*)[40])(frame_ + FRAME_OFF(12)))
void __cdecl text_expand_vars(iptr param_1,iptr param_2)

{
  char *pcVar1;
  int iVar2;
  size_t sVar3;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i8 *)param_2 = 0;
  do {
    pcVar1 = _strchr((char *)param_1,0x25);
    if (pcVar1 != (char *)0x0) {
      *pcVar1 = '\0';
    }
    if (*(char *)param_1 != '\0') {
      FUN_005f22e0(param_2,param_1);
    }
    local_34 = pcVar1;
    if (pcVar1 != (char *)0x0) {
      local_34 = pcVar1 + 1;
      iVar2 = __strnicmp(local_34,s_STRING_00625e40,6);
      if (iVar2 == 0) {
        iVar2 = _atoi(pcVar1 + 7);
        FUN_005f22e0(param_2,&text_string_args + iVar2 * 0x104);
        param_1 = (iptr)(pcVar1 + 8);
        if (9 < iVar2) {
          param_1 = (iptr)(pcVar1 + 9);
        }
      }
      else {
        iVar2 = _strncmp(local_34,s_NUMBER_00625e48,6);
        if (iVar2 == 0) {
          iVar2 = _atoi(pcVar1 + 7);
          __ltoa(*(long *)(&text_number_args + iVar2 * 4),local_2c,10);
          FUN_005f22e0(param_2,local_2c);
          param_1 = (iptr)(pcVar1 + 8);
        }
        else {
          iVar2 = _strncmp(local_34,&text_var_hex_tag_str,3);
          if (iVar2 == 0) {
            iVar2 = _atoi(pcVar1 + 4);
            __ltoa(*(long *)(&text_number_args + iVar2 * 4),local_2c,0x10);
            for (local_30 = 0; sVar3 = _strlen(local_2c), local_30 < 4 - sVar3;
                local_30 = local_30 + 1) {
              FUN_005f22e0(param_2,&text_var_hex_pad_str);
            }
            FUN_005f22e0(param_2,local_2c);
            param_1 = (iptr)(pcVar1 + 5);
          }
          else {
            param_1 = (iptr)local_34;
            if (*local_34 == '%') {
              FUN_005f22e0(param_2,&text_var_percent_str);
              param_1 = (iptr)(pcVar1 + 2);
            }
          }
        }
      }
    }
  } while (local_34 != (char *)0x0);
  return;
}
#undef local_34
#undef local_30
#undef local_2c

/* 004271e8 auto */
i32 __cdecl text_set_label_arg(i32 param_1,i32 param_2)

{
  iptr iVar1;
  i32 uVar2;
  
  iVar1 = label_string(param_2);
  uVar2 = text_set_string_arg_b(param_1,iVar1);
  return uVar2;
}

/* 004289e0 auto */
void __cdecl strpool_block_global_init(void)

{
  strpool_block_static_init();
  return;
}

/* 004289f5 auto */
void __cdecl strpool_block_static_init(void)

{
  memblock_ctor((MemBlock *)&strpool_block);
  return;
}

/* 00428a0f auto */
#define strpool_count (*(i32 *)((u8 *)&g.d_00625e60))
void __cdecl strpool_init(uint param_1)

{
  if (strpool_initialized == 0) {
    strpool_initialized = 1;
    memblock_init(ADDR(0x63e4c0, ((u8 *)&g.d_0063e4c0)),2,param_1);
  }
  else {
    memblock_free(ADDR(0x63e4c0, ((u8 *)&g.d_0063e4c0)));
    memblock_init(ADDR(0x63e4c0, ((u8 *)&g.d_0063e4c0)),2,param_1);
  }
  strpool_count = 0;
  return;
}
#undef strpool_count

/* 00428a78 auto */
void __cdecl strpool_free(void)

{
  memblock_free(ADDR(0x63e4c0, ((u8 *)&g.d_0063e4c0)));
  return;
}

/* 00428a95 auto */
#define strpool_count (*(int *)((u8 *)&g.d_00625e60))
#define strpool_last_string (*(i32 *)((u8 *)&g.d_0063e4b8))
int __cdecl strpool_add(iptr param_1)

{
  size_t sVar1;
  int iVar2;
  
  sVar1 = _strlen((char *)param_1);
  if (sVar1 == 0) {
    iVar2 = 0;
  }
  else {
    sVar1 = _strlen((char *)param_1);
    strpool_last_string = memblock_alloc(ADDR(0x63e4c0, ((u8 *)&g.d_0063e4c0)),sVar1 + 1);
    FUN_005f22d0(strpool_last_string,param_1);
    iVar2 = strpool_count;
    strpool_count++;
  }
  return iVar2;
}
#undef strpool_count
#undef strpool_last_string

/* 00428b0c auto */
#define local_8 (*(char * *)(frame_ + FRAME_OFF(0)))
char * __cdecl label_string(int param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = strpool_data;
  for (; param_1 != 0; param_1--) {
    for (; *local_8 != '\0'; local_8++) {
    }
    for (; *local_8 == '\0'; local_8++) {
    }
  }
  return local_8;
}
#undef local_8

/* 00428b68 auto */
#define strpool_count (*(int *)((u8 *)&g.d_00625e60))
#define strpool_last_string (*(char * *)((u8 *)&g.d_0063e4b8))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl strpool_add_padded(iptr param_1,uint param_2)

{
  int iVar1;
  size_t sVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  sVar2 = _strlen((char *)param_1);
  if ((int)param_2 < (int)(sVar2 + 1)) {
    sVar2 = _strlen((char *)param_1);
    local_8 = sVar2 + 1;
  }
  else {
    local_8 = param_2;
  }
  strpool_last_string = (char *)memblock_alloc(ADDR(0x63e4c0, ((u8 *)&g.d_0063e4c0)),local_8);
  _memset(strpool_last_string,0,local_8);
  _strncpy(strpool_last_string,(char *)param_1,local_8);
  sVar2 = _strlen((char *)param_1);
  if (sVar2 == 0) {
    *strpool_last_string = ' ';
  }
  iVar1 = strpool_count;
  strpool_count++;
  return iVar1;
}
#undef strpool_count
#undef strpool_last_string
#undef local_8

/* 0043c430 auto */
/* Library Function - Single Match
    public: __thiscall _Timevec::~_Timevec(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dll_free(DllHandle *this)

{
  dll_unload(this->hmodule);
  return;
}

/* 0043c810 auto */
void __cdecl text_append_period(void)

{
  str_append_period(ADDR(0x679640, ((u8 *)&g.d_00679640)));
  return;
}

/* 0043c840 auto */
void __cdecl str_append(iptr param_1,iptr param_2)

{
  FUN_005f22e0(param_1,param_2);
  return;
}

/* 0043c870 auto */
void __cdecl text_append_long(i32 param_1)

{
  str_append_long(ADDR(0x679640, ((u8 *)&g.d_00679640)),param_1);
  return;
}

/* 0043c8a0 auto */
void __cdecl text_append_gold(i32 param_1)

{
  str_append_gold(ADDR(0x679640, ((u8 *)&g.d_00679640)),param_1);
  return;
}

/* 0043ca50 auto */
void __cdecl text_append_population(iptr civ,i32 param_2)

{
  str_append_population(ADDR(0x679640, ((u8 *)&g.d_00679640)),civ,param_2);
  return;
}

/* 0043ca80 auto */
void __cdecl text_append_city_name(iptr city)

{
  str_append_city_name(ADDR(0x679640, ((u8 *)&g.d_00679640)),city);
  return;
}

/* 0043cda6 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl str_append_population(iptr param_1,iptr civ,int param_3)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_3 < 0) {
    local_8 = civ_total_population(civ);
  }
  else {
    local_8 = param_3;
  }
  if (99 < local_8) {
    str_append_int(param_1,local_8 / 100);
    FUN_005f22e0(param_1,&pop_thousands_sep_str);
    local_8 = local_8 % 100;
    if (local_8 < 10) {
      FUN_005f22e0(param_1,&pop_zero_pad_str);
    }
  }
  str_append_int(param_1,local_8);
  FUN_005f22e0(param_1,s_0_000_00626240);
  return;
}
#undef local_8

/* 0043ce5a auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl str_append_city_population(iptr param_1,iptr city)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = city_population_units(city);
  if (99 < local_8) {
    str_append_int(param_1,local_8 / 100);
    FUN_005f22e0(param_1,&city_pop_thousands_sep_str);
    local_8 = local_8 % 100;
    if (local_8 < 10) {
      FUN_005f22e0(param_1,&city_pop_zero_pad_str);
    }
  }
  str_append_int(param_1,local_8);
  FUN_005f22e0(param_1,s_0_000_00626250);
  return;
}
#undef local_8

/* 0043f444 auto */
void __cdecl str_append_city_name(iptr param_1,int city)

{
  if (city < 0) {
    str_append_label(param_1,0xe);
  }
  else {
    str_concat(param_1,(iptr)&cities[city].name);
  }
  return;
}

/* 004502b0 auto */
DllHandle * __thiscall dll_handle_init(DllHandle *this)

{
  this->hmodule = 0;
  return this;
}

/* 004502e0 auto */
void __thiscall dll_handle_load(DllHandle *this,iptr param_1)

{
  u32 uVar1;
  
  if (this->hmodule != 0) {
    dll_unload(this->hmodule);
  }
  uVar1 = res_dll_load_library(param_1);
  this->hmodule = uVar1;
  return;
}

/* 00450340 auto */
void __thiscall dll_handle_free(DllHandle *this)

{
  if (this->hmodule != 0) {
    dll_unload(this->hmodule);
  }
  this->hmodule = 0;
  return;
}

/* 00467580 auto */
void __cdecl text_set_number_arg_v(int param_1,i32 param_2)

{
  *(i32 *)(&text_number_args + param_1 * 4) = param_2;
  return;
}

/* 0046a740 auto */
#define label_count (*(i32 *)((u8 *)&g.d_00628424))
#define label_ids_handle (*(int *)((u8 *)&g.d_0062841c))
void __cdecl labels_free(void)

{
  if (label_ids_handle != 0) {
    mem_unlock_handle(label_ids_handle);
    mem_free_handle(label_ids_handle);
    label_ids_handle = 0;
  }
  label_count = 0;
  return;
}
#undef label_count
#undef label_ids_handle

/* 0046a78d auto */
#define label_count (*(int *)((u8 *)&g.d_00628424))
#define label_ids_handle (*(iptr *)((u8 *)&g.d_0062841c))
#define local_110 (*(i8 (*)[260])(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(260)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(264)))
int __cdecl labels_load(void)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(272)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = -1;
  iVar1 = text_open_section(ADDR(0x628430, ((u8 *)&g.d_00628430)),ADDR(0x628428, ((u8 *)&g.d_00628428)));
  if (iVar1 == 0) {
    text_read_line(1);
    label_count = text_next_int();
    label_ids_handle = mem_handle_alloc_tracked(0xde0);
    if (label_ids_handle == 0) {
      error_report(0xfffffff7,4,0,0x378,4);
    }
    else {
      label_string_ids = mem_lock_handle(label_ids_handle);
      if (label_string_ids == 0) {
        error_report(0xfffffff6,4,0,label_ids_handle,0x378);
      }
      else {
        for (local_c = 0; local_c < label_count; local_c++) {
          uVar2 = text_read_line_pooled();
          *(i32 *)(label_string_ids + local_c * 4) = uVar2;
        }
        if (local_c < 0x378) {
          FUN_005f22d0(local_110,&scenario_dir_path);
          FUN_005f22d0(&scenario_dir_path,&game_home_dir);
          iVar1 = text_open_section(ADDR(0x628440, ((u8 *)&g.d_00628440)),ADDR(0x628438, ((u8 *)&g.d_00628438)));
          if (iVar1 == 0) {
            text_read_line(1);
            iVar1 = text_next_int();
            for (local_c = 0; local_c < label_count; local_c++) {
              text_read_line(1);
            }
            for (; local_c < iVar1; local_c++) {
              uVar2 = text_read_line_pooled();
              *(i32 *)(label_string_ids + local_c * 4) = uVar2;
            }
          }
          FUN_005f22d0(&scenario_dir_path,local_110);
          if (local_c < 0x378) {
            uVar2 = strpool_add(ADDR(0x628448, ((u8 *)&g.d_00628448)));
            for (; local_c < 0x378; local_c++) {
              *(i32 *)(label_string_ids + local_c * 4) = uVar2;
            }
          }
        }
        local_8 = local_c;
      }
    }
  }
  else {
    error_report(0xfffffff8,4,0,0,0);
  }
  text_close_file();
  if (local_8 < 1) {
    labels_free();
  }
  return local_8;
}
#undef label_count
#undef label_ids_handle
#undef local_110
#undef local_c
#undef local_8

/* 0046e8f0 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl str_parse_hex(iptr param_1)

{
  char cVar1;
  int _C;
  int iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  while (*(char *)param_1 != '\0') {
    cVar1 = *(char *)param_1;
    param_1++;
    _C = FUN_005f2700((int)cVar1);
    iVar2 = _isdigit(_C);
    if (iVar2 == 0) {
      if ((_C < 0x41) || (0x46 < _C)) {
        for (; *(char *)param_1 != '\0'; param_1++) {
        }
      }
      else {
        local_8 = local_8 * 0x10 + _C - 0x37;
      }
    }
    else {
      local_8 = local_8 * 0x10 + _C - 0x30;
    }
  }
  return local_8;
}
#undef local_8

/* 00485208 auto */
#define scenario_year_increment (*(short *)((u8 *)&g.d_0064bcb4))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl str_append_year(iptr param_1,uint param_2)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((game.game_flags & 0x80) == 0) || (-1 < scenario_year_increment)) {
    if ((-1 < (int)param_2) && (game_language == 0)) {
      str_append_label(param_1,1);
      str_append_space(param_1);
    }
    if ((int)param_2 < 1) {
      local_14 = ~param_2 + 1;
    }
    else {
      local_14 = param_2;
    }
    str_append_int(param_1,local_14);
    if ((-1 < (int)param_2) && (game_language != 0)) {
      str_append_space(param_1);
      str_append_label(param_1,1);
    }
    if ((int)param_2 < 0) {
      str_append_space(param_1);
      str_append_label(param_1,0);
    }
  }
  else {
    if ((int)param_2 < 1) {
      if ((int)param_2 % 0xc < 1) {
        local_c = ~((int)param_2 % 0xc) + 1;
      }
      else {
        local_c = (int)param_2 % 0xc;
      }
      text_append_label(0x1af - local_c);
    }
    else {
      if ((int)param_2 % 0xc < 1) {
        local_8 = ~((int)param_2 % 0xc) + 1;
      }
      else {
        local_8 = (int)param_2 % 0xc;
      }
      text_append_label(local_8 + 0x1a4);
    }
    text_append_space();
    if ((int)param_2 / 0xc < 1) {
      local_10 = ~((int)param_2 / 0xc) + 1;
    }
    else {
      local_10 = (int)param_2 / 0xc;
    }
    str_append_int(param_1,local_10);
  }
  return;
}
#undef scenario_year_increment
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 004929c0 auto */
/* Library Function - Multiple Matches With Same Base Name
    protected: virtual unsigned char * __thiscall CHtmlStream::Realloc(unsigned char *,unsigned
   long)
    protected: virtual unsigned char * __thiscall CMemFile::Realloc(unsigned char *,unsigned long)
   
   Library: Visual Studio 1998 Debug */

i32 __thiscall file_obj_open(FileObject *this,iptr param_1)

{
  i32 uVar1;
  
  uVar1 = file_obj_open_path(param_1,(iptr)this);
  return uVar1;
}

/* 00492a00 auto */
/* Library Function - Multiple Matches With Same Base Name
    protected: virtual unsigned char * __thiscall CHtmlStream::Realloc(unsigned char *,unsigned
   long)
    protected: virtual unsigned char * __thiscall CMemFile::Realloc(unsigned char *,unsigned long)
   
   Library: Visual Studio 1998 Debug */

i32 __thiscall file_obj_seek_cur(FileSeekView *this,i32 param_1)

{
  i32 uVar1;
  
  uVar1 = file_obj_seek_rel((iptr)this,param_1);
  return uVar1;
}

/* 00492a40 auto */
void __thiscall file_obj_read_line(FileReadLineView *this,iptr param_1,i32 param_2)

{
  file_obj_read_line_impl((iptr)this,param_1,param_2);
  return;
}

/* 00492a80 auto */
i32 __thiscall file_obj_get_size(FileObject *this)

{
  i32 uVar1;
  
  uVar1 = file_obj_get_size_impl((iptr)this);
  return uVar1;
}

/* 004a2020 auto */
#define text_file_handle (*(FILE * *)((u8 *)&g.d_0062cd20))
void __cdecl text_close_file(void)

{
  if (text_file_handle != (FILE *)0x0) {
    _fclose(text_file_handle);
    text_file_handle = (FILE *)0x0;
  }
  return;
}
#undef text_file_handle

/* 004a2055 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define text_file_handle (*(FILE * *)((u8 *)&g.d_0062cd20))
#define text_line_cursor (*(i8 * *)((u8 *)&g.d_00673f14))
#define local_264 (*(char (*)[80])(frame_ + FRAME_OFF(4)))
#define local_214 (*(int *)(frame_ + FRAME_OFF(84)))
#define name2 (*(char (*)[260])(frame_ + FRAME_OFF(88)))
#define local_10c (*(char (*)[260])(frame_ + FRAME_OFF(348)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(608)))
int __cdecl text_open_file_section(int param_1,int param_2)

{
  bool bVar1;
  bool bVar2;
  size_t sVar3;
  char *pcVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(616)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_214 = 1;
  bVar2 = false;
  local_8 = -1;
  str_clear((iptr)name2);
  str_clear((iptr)local_264);
  if (param_2 != 0) {
    local_264[0] = '@';
    local_264[1] = 0;
    FUN_005f22e0(local_264,param_2);
    __strupr(local_264);
  }
  if (param_1 == 0) {
    bVar2 = true;
  }
  else {
    text_close_file();
    FUN_005f22d0(name2,param_1);
    path_default_extension((iptr)name2,ADDR(0x62cd24, ((u8 *)&g.d_0062cd24)));
    __getcwd(local_10c,0x104);
    __chdir(&scenario_dir_path);
    text_file_handle = (FILE *)file_open_path((iptr)name2,ADDR(0x62cd28, ((u8 *)&g.d_0062cd28)));
    if ((text_file_handle != (FILE *)0x0) && (sVar3 = _strlen(name2), sVar3 != 0)) {
      local_8 = text_section_index_lookup((iptr)name2,(iptr)local_264);
    }
    __chdir(&game_home_dir);
    if (((text_file_handle == (FILE *)0x0) &&
        (text_file_handle = (FILE *)file_open_path((iptr)name2,ADDR(0x62cd2c, ((u8 *)&g.d_0062cd2c))),
        text_file_handle != (FILE *)0x0)) && (sVar3 = _strlen(name2), sVar3 != 0)) {
      local_8 = text_section_index_lookup((iptr)name2,(iptr)local_264);
    }
    __chdir(local_10c);
    if (text_file_handle == (FILE *)0x0) goto LAB_004a2348;
  }
  if (param_2 == 0) {
    local_214 = 0;
  }
  else {
    if (0 < local_8) {
      _fseek(text_file_handle,local_8,0);
    }
    bVar1 = false;
    while (!bVar1) {
      if ((CRT_FEOF(text_file_handle)) != 0) {
        if (!bVar2) goto LAB_004a2348;
        bVar2 = false;
        _rewind(text_file_handle);
      }
      pcVar4 = _fgets(&text_buffer,0xff,text_file_handle);
      if (pcVar4 != (char *)0x0) {
        str_strip_newline(ADDR(0x679640, ((u8 *)&g.d_00679640)));
        str_trim(ADDR(0x679640, ((u8 *)&g.d_00679640)));
        iVar5 = __strcmpi(&text_buffer,local_264);
        if (iVar5 == 0) {
          bVar1 = true;
        }
      }
    }
    sVar3 = _strlen(&text_buffer);
    text_line_cursor = &text_buffer + sVar3;
    local_214 = 0;
  }
LAB_004a2348:
  if (local_214 != 0) {
    text_close_file();
  }
  return local_214;
}
#undef text_buffer
#undef text_file_handle
#undef text_line_cursor
#undef local_264
#undef local_214
#undef name2
#undef local_10c
#undef local_8

/* 004a2379 auto */
#define local_10c (*(i8 (*)[260])(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(264)))
int __cdecl text_open_section(iptr param_1,iptr param_2)

{
  i8 frame_[FRAME_OFF(272)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = text_open_file_section(param_1,param_2);
  if (local_8 != 0) {
    FUN_005f22d0(local_10c,&scenario_dir_path);
    FUN_005f22d0(&scenario_dir_path,&game_home_dir);
    local_8 = text_open_file_section(param_1,param_2);
    FUN_005f22d0(&scenario_dir_path,local_10c);
  }
  return local_8;
}
#undef local_10c
#undef local_8

/* 004a23fc auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define text_file_handle (*(FILE * *)((u8 *)&g.d_0062cd20))
#define text_line_cursor (*(i8 * *)((u8 *)&g.d_00673f14))
#define local_8 (*(i8 * *)(frame_ + FRAME_OFF(0)))
i8 * __cdecl text_read_line(int param_1)

{
  char *pcVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (i8 *)0x0;
  if (((CRT_FEOF(text_file_handle)) == 0) &&
     (pcVar1 = _fgets(&text_buffer,0xff,text_file_handle), pcVar1 != (char *)0x0)) {
    str_strip_newline(ADDR(0x679640, ((u8 *)&g.d_00679640)));
    if (param_1 == 1) {
      str_trim(ADDR(0x679640, ((u8 *)&g.d_00679640)));
    }
    text_line_cursor = &text_buffer;
    local_8 = &text_buffer;
  }
  if (local_8 == (i8 *)0x0) {
    text_buffer = 0;
    text_close_file();
  }
  return local_8;
}
#undef text_buffer
#undef text_file_handle
#undef text_line_cursor
#undef local_8

/* 004a24b1 auto */
#define text_line_cursor (*(char * *)((u8 *)&g.d_00673f14))
#define text_token_buf (*(i8 *)((u8 *)&g.d_00673e10))
#define local_8 (*(char * *)(frame_ + FRAME_OFF(0)))
i8 * __cdecl text_next_token(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = &text_token_buf;
  for (; (*text_line_cursor != '\0' && (*text_line_cursor != ',')); text_line_cursor++) {
    *local_8 = *text_line_cursor;
    local_8++;
  }
  if (*text_line_cursor != '\0') {
    text_line_cursor++;
  }
  *local_8 = '\0';
  str_trim(ADDR(0x673e10, ((u8 *)&g.d_00673e10)));
  return &text_token_buf;
}
#undef text_line_cursor
#undef text_token_buf
#undef local_8

/* 004a2534 auto */
i32 __cdecl text_next_int(void)

{
  iptr iVar1;
  i32 uVar2;
  
  iVar1 = text_next_token();
  uVar2 = str_parse_int_prefixed(iVar1);
  return uVar2;
}

/* 004a257a auto */
i32 __cdecl text_read_line_pooled(void)

{
  i32 uVar1;
  
  text_read_line(1);
  uVar1 = strpool_add(ADDR(0x679640, ((u8 *)&g.d_00679640)));
  return uVar1;
}

/* 004a25aa auto */
i32 __cdecl text_next_token_pooled(void)

{
  i32 uVar1;
  
  text_next_token();
  uVar1 = strpool_add(ADDR(0x673e10, ((u8 *)&g.d_00673e10)));
  return uVar1;
}

/* 004a25d5 auto */
#define text_token_buf (*(i8 *)((u8 *)&g.d_00673e10))
#define local_c (*(char * *)(frame_ + FRAME_OFF(4)))
short __cdecl text_next_binary(void)

{
  short sVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  sVar1 = 0;
  text_next_token();
  for (local_c = &text_token_buf; (*local_c == '0' || (*local_c == '1')); local_c++) {
    sVar1 = sVar1 * 2;
    if (*local_c == '1') {
      sVar1++;
    }
  }
  return sVar1;
}
#undef text_token_buf
#undef local_c

/* 004a2645 auto */
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
i32 __cdecl text_read_section_line(iptr param_1,iptr param_2,iptr param_3)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 1;
  iVar1 = text_open_section(param_1,param_2);
  if (iVar1 == 0) {
    for (local_8 = 0; local_8 <= param_3; local_8++) {
      text_read_line(1);
    }
    local_c = 0;
  }
  text_close_file();
  return local_c;
}
#undef local_c
#undef local_8

/* 004a26bf auto */
i32 __cdecl text_next_token_str_id(i32 param_1)

{
  i32 uVar1;
  
  text_next_token();
  uVar1 = strpool_add_padded(ADDR(0x673e10, ((u8 *)&g.d_00673e10)),param_1);
  return uVar1;
}

/* 004aef20 auto */
iptr __cdecl str_clear(iptr param_1)

{
  *(i8 *)param_1 = 0;
  return param_1;
}

/* 004aef36 auto */
void __cdecl str_append_space(iptr param_1)

{
  FUN_005f22e0(param_1,&append_space_str);
  return;
}

/* 004aef57 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl str_append_spaces(iptr param_1,int param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < param_2; local_8++) {
    str_append_space(param_1);
  }
  return;
}
#undef local_8

/* 004aef96 auto */
void __cdecl str_append_comma(iptr param_1)

{
  FUN_005f22e0(param_1,&append_comma_str);
  return;
}

/* 004aefb7 auto */
void __cdecl str_append_colon(iptr param_1)

{
  FUN_005f22e0(param_1,&append_colon_str);
  return;
}

/* 004aefd8 auto */
void __cdecl str_append_period(iptr param_1)

{
  FUN_005f22e0(param_1,&append_period_str);
  return;
}

/* 004aeff9 auto */
void __cdecl str_append_percent(iptr param_1)

{
  FUN_005f22e0(param_1,&append_percent_str);
  return;
}

/* 004af01a auto */
void __cdecl str_append_lparen(iptr param_1)

{
  FUN_005f22e0(param_1,&append_lparen_str);
  return;
}

/* 004af03b auto */
void __cdecl str_append_rparen(iptr param_1)

{
  FUN_005f22e0(param_1,&append_rparen_str);
  return;
}

/* 004af09e auto */
void __cdecl str_append_plus(iptr param_1)

{
  FUN_005f22e0(param_1,&append_plus_str);
  return;
}

/* 004af122 auto */
void __cdecl str_append_string_id(iptr param_1,i32 param_2)

{
  i32 uVar1;
  
  uVar1 = label_string(param_2);
  FUN_005f22e0(param_1,uVar1);
  return;
}

/* 004af14b auto */
void __cdecl str_append_label(iptr param_1,int param_2)

{
  str_append_string_id(param_1,*(i32 *)(label_string_ids + param_2 * 4));
  return;
}

/* 004af174 auto */
void __cdecl str_concat(iptr param_1,iptr param_2)

{
  FUN_005f22e0(param_1,param_2);
  return;
}

/* 004af1d5 auto */
#define local_18 (*(char (*)[20])(frame_ + FRAME_OFF(0)))
i32 __cdecl str_append_int(iptr param_1,int param_2)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  __itoa(param_2,local_18,10);
  uVar1 = FUN_005f22e0(param_1,local_18);
  return uVar1;
}
#undef local_18

/* 004af284 auto */
#define local_18 (*(char (*)[20])(frame_ + FRAME_OFF(0)))
void __cdecl str_append_long(iptr param_1,long param_2)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  __ltoa(param_2,local_18,10);
  FUN_005f22e0(param_1,local_18);
  return;
}
#undef local_18

/* 004af2b9 auto */
void __cdecl str_append_gold(iptr param_1,i32 param_2)

{
  str_append_long(param_1,param_2);
  text_append_space();
  text_append_label(0x143);
  return;
}

/* 004bb370 auto */
void __thiscall file_obj_read(FileObject *this,iptr param_1,i32 param_2)

{
  file_obj_read_bytes((iptr)this,param_1,param_2);
  return;
}

/* 004befd1 auto */
void __cdecl text_list_append_wrapped(iptr param_1,i32 param_2,iptr param_3,iptr param_4)

{
  if (*(int *)param_3 == 0) {
    text_append_lparen();
  }
  else {
    text_append(ADDR(0x62db88, ((u8 *)&g.d_0062db88)));
    if (*(int *)param_4 < 4) {
      text_append(ADDR(0x62db8c, ((u8 *)&g.d_0062db8c)));
    }
    else {
      *(i32 *)param_4 = 0;
      dialog_add_line
                ((DialogAddLineView *)param_1,ADDR(0x679640, ((u8 *)&g.d_00679640)),0xffffffff,0xffffffff,0xffffffff,0);
      text_clear();
    }
  }
  *(int *)param_4 = *(int *)param_4 + 1;
  *(int *)param_3 = *(int *)param_3 + 1;
  text_append_string_id(param_2);
  return;
}

/* 004c4210 auto */
void __cdecl text_set_number_arg_u8(int param_1,uint param_2)

{
  *(uint *)(&text_number_args + param_1 * 4) = param_2 & 0xff;
  return;
}

/* 004ccdb6 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_18 (*(char (*)[20])(frame_ + FRAME_OFF(0)))
void __cdecl text_append_int_2d(i32 param_1)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  _sprintf(local_18,&int_2d_fmt,param_1);
  FUN_005f22e0(&text_buffer,local_18);
  return;
}
#undef text_buffer
#undef local_18

/* 004ccdef auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_8 (*(size_t *)(frame_ + FRAME_OFF(0)))
void __cdecl text_append_advance_abbrev(iptr advance,int param_2)

{
  size_t sVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (advance == -2) {
    FUN_005f22e0(&text_buffer,&advance_abbrev_no_strs + ((param_2 != 0) - 1 & 8));
  }
  else if (advance == -1) {
    FUN_005f22e0(&text_buffer,&advance_abbrev_nil_strs + ((param_2 != 0) - 1 & 8));
  }
  else if (advance < 100) {
    FUN_005f22e0(&text_buffer,advances + advance);
    if (param_2 != 0) {
      FUN_005f22e0(&text_buffer,&advance_abbrev_comma_str);
    }
    sVar1 = _strlen(advances[advance].abbrev);
    if (sVar1 < 3) {
      local_8 = _strlen(advances[advance].abbrev);
    }
    else {
      local_8 = 3;
    }
    text_append_spaces(3 - local_8);
  }
  else {
    FUN_005f22e0(&text_buffer,&advance_abbrev_err_strs + ((param_2 != 0) - 1 & 8));
  }
  return;
}
#undef text_buffer
#undef local_8

/* 004cfff0 auto */
#define local_8 (*(char * *)(frame_ + FRAME_OFF(0)))
void __cdecl str_trim_trailing(iptr param_1)

{
  uptr sVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  sVar1 = _strlen((char *)param_1);
  if (sVar1 != 0) {
    for (local_8 = (char *)((sVar1 - 1) + param_1);
        ((uint)param_1 <= local_8 &&
        (((*local_8 == ' ' || (*local_8 == '\t')) && (*local_8 = '\0', local_8 != (char *)param_1)))
        ); local_8--) {
    }
  }
  return;
}
#undef local_8

/* 004d007e auto */
#define local_108 (*(char * *)(frame_ + FRAME_OFF(0)))
#define local_104 (*(i8 (*)[256])(frame_ + FRAME_OFF(4)))
void __cdecl str_trim(iptr param_1)

{
  i8 frame_[FRAME_OFF(264)] __attribute__((aligned(8)));  /* original stack frame */
  
  str_trim_trailing(param_1);
  for (local_108 = (char *)param_1;
      (*local_108 != '\0' && ((*local_108 == ' ' || (*local_108 == '\t'))));
      local_108 = local_108 + 1) {
  }
  FUN_005f22d0(local_104,local_108);
  FUN_005f22d0(param_1,local_104);
  return;
}
#undef local_108
#undef local_104

/* 004db210 auto */
void __cdecl text_section_index_global_init(void)

{
  text_section_index_static_init();
  return;
}

/* 004db225 auto */
void __cdecl text_section_index_static_init(void)

{
  memblock_ctor((MemBlock *)&text_section_index_pool);
  return;
}

/* 004db23f auto */
#define text_section_index_count (*(int *)((u8 *)&g.d_0062e610))
#define text_section_index_valid (*(i32 *)((u8 *)&g.d_0062e60c))
#define local_108 (*(char *)(frame_ + FRAME_OFF(0)))
#define local_107 (*(char *)(frame_ + FRAME_OFF(1)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(256)))
void __cdecl text_section_index_build(iptr param_1,uint param_2)

{
  FILE *_File;
  long lVar1;
  char *pcVar2;
  size_t sVar3;
  long *plVar4;
  i8 frame_[FRAME_OFF(264)] __attribute__((aligned(8)));  /* original stack frame */
  
  memblock_free(ADDR(0x6a5b38, ((u8 *)&g.d_006a5b38)));
  memblock_init(ADDR(0x6a5b38, ((u8 *)&g.d_006a5b38)),1,param_2);
  text_section_index_valid = 0;
  text_section_index_count = 0;
  __getcwd(&text_section_index_path,0x104);
  FUN_005f22e0(&text_section_index_path,&text_index_path_sep_str);
  FUN_005f22e0(&text_section_index_path,param_1);
  path_default_extension(ADDR(0x62e508, ((u8 *)&g.d_0062e508)),ADDR(0x62cd24, ((u8 *)&g.d_0062cd24)));
  _File = (FILE *)file_open_path(ADDR(0x62e508, ((u8 *)&g.d_0062e508)),ADDR(0x62e618, ((u8 *)&g.d_0062e618)));
  if (_File == (FILE *)0x0) {
    text_section_index_path = 0;
  }
  else {
    while ((CRT_FEOF(_File)) == 0) {
      lVar1 = _ftell(_File);
      pcVar2 = _fgets(&local_108,0xff,_File);
      if (pcVar2 == (char *)0x0) break;
      str_strip_newline((iptr)&local_108);
      str_trim((iptr)&local_108);
      if (((local_108 == '@') && ('@' < local_107)) && (local_107 < '[')) {
        sVar3 = _strlen(&local_108);
        local_8 = sVar3 + 5;
        if ((int)(uint)text_section_pool_free_bytes < (int)local_8) break;
        plVar4 = (long *)memblock_alloc(ADDR(0x6a5b38, ((u8 *)&g.d_006a5b38)),local_8);
        *plVar4 = lVar1;
        FUN_005f22d0(plVar4 + 1,&local_108);
        text_section_index_count++;
      }
    }
    text_section_index_valid = 1;
    _fclose(_File);
  }
  return;
}
#undef text_section_index_count
#undef text_section_index_valid
#undef local_108
#undef local_107
#undef local_8

/* 004db450 auto */
#define text_section_index_count (*(i32 *)((u8 *)&g.d_0062e610))
#define text_section_index_valid (*(i32 *)((u8 *)&g.d_0062e60c))
void __cdecl text_section_index_free(void)

{
  text_section_index_valid = 0;
  text_section_index_count = 0;
  memblock_free(ADDR(0x6a5b38, ((u8 *)&g.d_006a5b38)));
  return;
}
#undef text_section_index_count
#undef text_section_index_valid

/* 004db481 auto */
#define text_section_index_count (*(int *)((u8 *)&g.d_0062e610))
#define text_section_index_valid (*(int *)((u8 *)&g.d_0062e60c))
#define local_114 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10c (*(char * *)(frame_ + FRAME_OFF(12)))
#define local_108 (*(char (*)[260])(frame_ + FRAME_OFF(16)))
i32 __cdecl text_section_index_lookup(iptr param_1,iptr param_2)

{
  char *pcVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (text_section_index_valid != 0) {
    __getcwd(local_108,0x104);
    FUN_005f22e0(local_108,&text_lookup_path_sep_str);
    FUN_005f22e0(local_108,param_1);
    iVar2 = __strcmpi(local_108,&text_section_index_path);
    if (iVar2 == 0) {
      local_10c = text_section_index_base;
      for (local_114 = 0; local_114 < text_section_index_count; local_114++) {
        iVar2 = __strcmpi(local_10c + 4,(char *)param_2);
        pcVar1 = local_10c + 4;
        if (iVar2 == 0) {
          return *(i32 *)local_10c;
        }
        while (local_10c = pcVar1, *local_10c != '\0') {
          pcVar1 = local_10c + 1;
        }
        local_10c++;
      }
    }
  }
  return 0xffffffff;
}
#undef text_section_index_count
#undef text_section_index_valid
#undef local_114
#undef local_10c
#undef local_108

/* 00506448 auto */
#define city (*(uint *)(frame_ + FRAME_OFF(4)))
void __cdecl text_set_unit_info_args(iptr unit)

{
  iptr iVar1;
  int x;
  int y;
  int iVar4;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  text_clear();
  iVar1 = civ_get_adjective((int)units[unit].owner);
  text_append(iVar1);
  if ((units[unit].flags & 0x2000) != 0) {
    text_append_space();
    text_append_label(0xd);
  }
  text_append_space();
  text_append_string_id(unit_types[units[unit].type].name);
  text_set_string_arg(0,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  text_clear();
  x = (int)units[unit].x;
  y = (int)units[unit].y;
  iVar4 = city_at(x,y);
  if (-1 < iVar4) {
    text_append(iVar4 * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
    text_append_space();
  }
  text_append_lparen();
  text_append_int(x);
  text_append_comma();
  text_append_int(y);
  text_append_rparen();
  if (iVar4 < 0) {
    x = city_find_nearest(x,y,-1,0xffffffff,-1);
    if (-1 < x) {
      text_append_space();
      text_append_lparen();
      text_append_label(0xb2);
      text_append_space();
      text_append(x * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
      text_append_rparen();
    }
  }
  text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  text_clear();
  if (units[unit].home_city == -1) {
    city = 0xffffffff;
  }
  else {
    city = (uint)(byte)units[unit].home_city;
  }
  text_append_city_name(city);
  text_set_string_arg(2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  return;
}
#undef city

/* 00511430 auto */
void __cdecl text_append_plus(void)

{
  str_append_plus(ADDR(0x679640, ((u8 *)&g.d_00679640)));
  return;
}

/* 005116f0 auto */
void __cdecl text_append_city_population(i32 city)

{
  str_append_city_population(ADDR(0x679640, ((u8 *)&g.d_00679640)),city);
  return;
}

/* 00553db0 auto */
int __cdecl str_find_bad_filename_char(iptr param_1)

{
  __strupr((char *)param_1);
  while ((*(char *)param_1 != '\0' && ((&filename_valid_chars)[*(char *)param_1] != '\0'))) {
    param_1++;
  }
  return (int)*(char *)param_1;
}

/* 00564470 auto */
#define app_hinstance (*(HMODULE *)((u8 *)&g.d_006e4ff0))
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(char * *)(frame_ + FRAME_OFF(8)))
i32 __cdecl file_require_cdrom(iptr param_1)

{
  iptr iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  GetModuleFileNameA(app_hinstance,&exe_dir_path,0x80);
  iVar1 = lstrlenA(&exe_dir_path);
  local_8 = &exe_dir_path + iVar1;
  do {
    if (local_8 == (char *)0x0) break;
    local_8--;
  } while (*local_8 != '\\');
  local_8[1] = '\0';
  do {
    for (local_c = 0; local_c < 2; local_c++) {
      iVar2 = file_find_fallback_drive(param_1);
      if (iVar2 != 0) {
        return 1;
      }
    }
    popup_game_flags(ADDR(0x633d5c, ((u8 *)&g.d_00633d5c)),0x2000001);
  } while (dlg_help_pressed != 0);
  return 0;
}
#undef app_hinstance
#undef dlg_help_pressed
#undef local_c
#undef local_8

/* 00564574 auto */
#define fallback_drive_root (*(i8 *)((u8 *)&g.d_006ab680))
i8 * __cdecl file_get_fallback_drive(void)

{
  i8 *puVar1;
  
  if (fallback_drive_root == '\0') {
    puVar1 = (i8 *)0x0;
  }
  else {
    puVar1 = &fallback_drive_root;
  }
  return puVar1;
}
#undef fallback_drive_root

/* 0056459f auto */
#define fallback_drive_root (*(i8 *)((u8 *)&g.d_006ab680))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_1a0 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_19c (*(_OFSTRUCT *)(frame_ + FRAME_OFF(4)))
#define local_114 (*(UINT *)(frame_ + FRAME_OFF(140)))
#define local_110 (*(CHAR (*)[256])(frame_ + FRAME_OFF(144)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(400)))
#define local_c (*(char * *)(frame_ + FRAME_OFF(404)))
#define local_8 (*(HFILE *)(frame_ + FRAME_OFF(408)))
i8 * __cdecl file_find_fallback_drive(iptr param_1)

{
  UINT uMode;
  DWORD DVar1;
  i8 *puVar2;
  i8 frame_[FRAME_OFF(416)] __attribute__((aligned(8)));  /* original stack frame */
  
  uMode = SetErrorMode(1);
  DVar1 = GetLogicalDrives();
  GetLogicalDriveStringsA(0x100,local_110);
  local_c = local_110;
  local_1a0 = 0;
  do {
    if (0x19 < local_1a0) {
LAB_005646e1:
      SetErrorMode(uMode);
      if (fallback_drive_root == '\0') {
        puVar2 = (i8 *)0x0;
      }
      else {
        puVar2 = &fallback_drive_root;
      }
      return puVar2;
    }
    local_10 = 1 << ((byte)local_1a0 & 0x1f);
    if ((DVar1 & local_10) != 0) {
      local_114 = GetDriveTypeA(local_c);
      if (local_114 == 3) {
        text_clear();
        text_append((iptr)local_c);
        text_append(param_1);
        local_8 = OpenFile(&text_buffer,&local_19c,0x4000);
        str_clear(ADDR(0x6ab680, ((u8 *)&g.d_006ab680)));
        fallback_drive_root = *local_c;
        fallback_drive_root_end = 0;
        str_append(ADDR(0x6ab680, ((u8 *)&g.d_006ab680)),ADDR(0x633d6c, ((u8 *)&g.d_00633d6c)));
        goto LAB_005646e1;
      }
      for (; *local_c != '\0'; local_c++) {
      }
      local_c++;
    }
    local_1a0++;
  } while( true );
}
#undef fallback_drive_root
#undef text_buffer
#undef local_1a0
#undef local_19c
#undef local_114
#undef local_110
#undef local_10
#undef local_c
#undef local_8

/* 00564713 auto */
#define fallback_drive_root (*(char *)((u8 *)&g.d_006ab680))
#define local_1a8 (*(CHAR (*)[128])(frame_ + FRAME_OFF(0)))
#define local_128 (*(i8 (*)[16])(frame_ + FRAME_OFF(128)))
#define local_118 (*(_OFSTRUCT *)(frame_ + FRAME_OFF(144)))
#define local_90 (*(CHAR (*)[128])(frame_ + FRAME_OFF(280)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(408)))
#define local_c (*(char * *)(frame_ + FRAME_OFF(412)))
#define local_8 (*(HFILE *)(frame_ + FRAME_OFF(416)))
i32 __cdecl file_resolve_path(iptr param_1)

{
  char *pcVar1;
  char cVar2;
  iptr iVar3;
  UINT uMode;
  i8 frame_[FRAME_OFF(424)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar3 = lstrlenA((LPCSTR)param_1);
  local_c = (char *)(param_1 + iVar3);
  local_10 = lstrlenA((LPCSTR)param_1);
  local_10++;
  for (; (local_10 != 0 && (*local_c != '\\')); local_c--) {
    local_10--;
  }
  local_c++;
  str_clear((iptr)local_128);
  str_clear((iptr)local_128);
  str_append((iptr)local_128,local_10 + param_1);
  uMode = SetErrorMode(1);
  str_clear((iptr)local_90);
  str_append((iptr)local_90,ADDR(0x6ab600, ((u8 *)&g.d_006ab600)));
  str_append((iptr)local_90,(iptr)local_128);
  local_8 = OpenFile(local_90,&local_118,0x4000);
  if ((local_8 == 0) || (local_8 == -1)) {
    local_c = (char *)param_1;
    do {
      if (*local_c == '\0') break;
      pcVar1 = local_c + 1;
      cVar2 = *local_c;
      local_c = pcVar1;
    } while (cVar2 != '\\');
    str_clear((iptr)local_1a8);
    str_append((iptr)local_1a8,ADDR(0x6ab600, ((u8 *)&g.d_006ab600)));
    if (*local_c == '\0') {
      str_append((iptr)local_1a8,param_1);
    }
    else {
      str_append((iptr)local_1a8,(iptr)local_c);
    }
    local_8 = OpenFile(local_1a8,&local_118,0x4000);
    if ((local_8 == 0) || (local_8 == -1)) {
      if (fallback_drive_root == '\0') {
        local_8 = 0;
      }
      else {
        str_clear((iptr)local_90);
        str_append((iptr)local_90,ADDR(0x6ab680, ((u8 *)&g.d_006ab680)));
        str_append((iptr)local_90,param_1);
        local_8 = OpenFile(local_90,&local_118,0x4000);
        if ((local_8 == 0) || (local_8 == -1)) {
          local_8 = 0;
        }
        else {
          str_clear((iptr)local_1a8);
          str_append((iptr)local_1a8,ADDR(0x6ab680, ((u8 *)&g.d_006ab680)));
          str_append((iptr)local_1a8,param_1);
          str_clear(param_1);
          str_append(param_1,(iptr)local_1a8);
          local_8 = 1;
        }
      }
    }
    else {
      str_clear(param_1);
      str_append(param_1,(iptr)local_1a8);
      local_8 = 1;
    }
  }
  else {
    str_clear(param_1);
    str_append(param_1,ADDR(0x6ab600, ((u8 *)&g.d_006ab600)));
    str_append(param_1,(iptr)local_128);
    local_8 = 1;
  }
  SetErrorMode(uMode);
  return local_8;
}
#undef fallback_drive_root
#undef local_1a8
#undef local_128
#undef local_118
#undef local_90
#undef local_10
#undef local_c
#undef local_8

/* 00564bf0 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl str_parse_int_prefixed(iptr param_1)

{
  char cVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(char *)param_1 == '0') {
    uVar2 = FUN_005f2700((uint)*(byte *)(param_1 + 1));
    cVar1 = (char)uVar2;
    if (cVar1 == 'X') {
      local_8 = str_parse_hex(param_1 + 2);
    }
    else if (cVar1 == 'B') {
      local_8 = str_parse_binary(param_1 + 2);
    }
    else if (cVar1 == 'D') {
      local_8 = _atoi((char *)(param_1 + 2));
    }
    else {
      local_8 = _atoi((char *)param_1);
    }
  }
  else {
    local_8 = _atoi((char *)param_1);
  }
  return local_8;
}
#undef local_8

/* 00578abd auto */
#define local_8 (*(char * *)(frame_ + FRAME_OFF(0)))
void __cdecl str_pipes_to_tabs(char *param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = param_1; *local_8 != '\0'; local_8++) {
    if (*local_8 == '|') {
      *local_8 = '\t';
    }
  }
  return;
}
#undef local_8

/* 00589fc9 auto */
#define local_5c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_58 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_54 (*(char (*)[80])(frame_ + FRAME_OFF(12)))
i32 __cdecl file_read_nth_line(iptr param_1,iptr param_2,int param_3)

{
  FILE *_File;
  char *pcVar1;
  size_t sVar2;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_5c = 1;
  _File = (FILE *)file_open_path(param_2,ADDR(0x634840, ((u8 *)&g.d_00634840)));
  if (_File != (FILE *)0x0) {
    for (local_58 = 1; local_58 <= param_3; local_58++) {
      if (((CRT_FEOF(_File)) != 0) ||
         (pcVar1 = _fgets(local_54,0x4c,_File), pcVar1 == (char *)0x0)) goto LAB_0058a0bc;
    }
    for (local_58 = 0; sVar2 = _strlen(local_54), local_58 < (int)sVar2; local_58++) {
      if (local_54[local_58] < ' ') {
        local_54[local_58] = '\0';
      }
    }
    FUN_005f22d0(param_1,local_54);
    local_5c = 0;
  }
LAB_0058a0bc:
  if (_File != (FILE *)0x0) {
    _fclose(_File);
  }
  return local_5c;
}
#undef local_5c
#undef local_58
#undef local_54

/* 0058a80d auto */
#define local_410 (*(i8 (*)[1024])(frame_ + FRAME_OFF(0)))
#define local_10 (*(FILE * *)(frame_ + FRAME_OFF(1024)))
#define local_c (*(size_t *)(frame_ + FRAME_OFF(1028)))
#define local_8 (*(FILE * *)(frame_ + FRAME_OFF(1032)))
void __cdecl file_copy(iptr param_1,iptr param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(1040)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = _strcmp((char *)param_1,(char *)param_2);
  if (iVar1 != 0) {
    local_10 = _fopen((char *)param_1,&file_copy_read_mode);
    if ((local_10 == (FILE *)0x0) ||
       (local_8 = _fopen((char *)param_2,&file_copy_write_mode), local_8 == (FILE *)0x0)) {
      MessageBoxA((HWND)0x0,s_Error_copying_file_00634954,(LPCSTR)0x0,0x10);
      if (local_10 != (FILE *)0x0) {
        _fclose(local_10);
      }
    }
    else {
      while (local_c = _fread(local_410,1,0x400,local_10), local_c != 0) {
        _fwrite(local_410,1,local_c,local_8);
      }
      _fclose(local_10);
      _fclose(local_8);
    }
  }
  return;
}
#undef local_410
#undef local_10
#undef local_c
#undef local_8

/* 005bad40 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl str_parse_binary(iptr param_1)

{
  char cVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  while (*(char *)param_1 != '\0') {
    cVar1 = *(char *)param_1;
    param_1++;
    iVar2 = FUN_005f2700((int)cVar1);
    if ((iVar2 == 0x30) || (iVar2 == 0x31)) {
      local_8 = local_8 * 2 + iVar2 - 0x30;
    }
    else {
      for (; *(char *)param_1 != '\0'; param_1++) {
      }
    }
  }
  return local_8;
}
#undef local_8

/* 005baeb0 auto */
void __cdecl text_set_surface(iptr param_1)

{
  text_draw_surface = param_1;
  return;
}

/* 005baec8 auto */
#define text_draw_font (*(iptr *)((u8 *)&g.d_006366ac))
void __cdecl text_set_font(iptr param_1)

{
  text_draw_font = param_1;
  return;
}
#undef text_draw_font

/* 005baee0 auto */
#define text_fg_color (*(i32 *)((u8 *)&g.d_006366b0))
#define text_shadow_color (*(i32 *)((u8 *)&g.d_006366b4))
#define text_shadow_dx (*(int *)((u8 *)&g.d_006366b8))
void __cdecl text_set_colors(i32 param_1,i32 param_2,int param_3,int param_4)

{
  text_fg_color = param_1;
  text_shadow_color = param_2;
  if (-1 < param_3) {
    text_shadow_dx = param_3;
  }
  if (-1 < param_4) {
    text_shadow_dy = param_4;
  }
  return;
}
#undef text_fg_color
#undef text_shadow_color
#undef text_shadow_dx

/* 005baf57 auto */
#define text_draw_font (*(GameFont * *)((u8 *)&g.d_006366ac))
#define text_fake_bold (*(int *)((u8 *)&g.d_006366c0))
#define text_fg_color (*(int *)((u8 *)&g.d_006366b0))
#define text_shadow_color (*(int *)((u8 *)&g.d_006366b4))
#define text_shadow_dx (*(int *)((u8 *)&g.d_006366b8))
int __cdecl text_draw_shadowed(iptr param_1,iptr param_2,int param_3,int param_4)

{
  int iVar1;
  
  if (-1 < text_shadow_color) {
    gfx_set_text_color_index(text_shadow_color);
    surface_draw_text
              ((DibSurface *)param_1,(iptr)text_draw_font,param_2,
               text_shadow_dx + text_fake_bold + param_3,text_shadow_dy + param_4,5);
  }
  if (-1 < text_fg_color) {
    gfx_set_text_color_index(text_fg_color);
    if (text_fake_bold != 0) {
      surface_draw_text
                ((DibSurface *)param_1,(iptr)text_draw_font,param_2,param_3 + 1,param_4,5);
    }
    surface_draw_text
              ((DibSurface *)param_1,(iptr)text_draw_font,param_2,param_3,param_4,5);
  }
  iVar1 = font_text_width(text_draw_font,param_2);
  return param_3 + iVar1;
}
#undef text_draw_font
#undef text_fake_bold
#undef text_fg_color
#undef text_shadow_color
#undef text_shadow_dx

/* 005bb024 auto */
#define text_draw_font (*(GameFont * *)((u8 *)&g.d_006366ac))
#define text_fake_bold (*(int *)((u8 *)&g.d_006366c0))
#define text_shadow_color (*(int *)((u8 *)&g.d_006366b4))
#define text_shadow_dx (*(uint *)((u8 *)&g.d_006366b8))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl text_draw_centered(iptr param_1,iptr param_2,int param_3,iptr param_4,int param_5)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = font_text_width(text_draw_font,param_2);
  if (-1 < text_shadow_color) {
    if ((int)text_shadow_dx < 1) {
      local_8 = local_8 + ~text_shadow_dx + 1;
    }
    else {
      local_8 += text_shadow_dx;
    }
  }
  iVar1 = local_8 + text_fake_bold;
  text_draw_shadowed(param_1,param_2,param_3 + ((param_5 >> 1) - (iVar1 >> 1)),param_4);
  return iVar1;
}
#undef text_draw_font
#undef text_fake_bold
#undef text_shadow_color
#undef text_shadow_dx
#undef local_8

/* 005bb0af auto */
#define text_draw_font (*(GameFont * *)((u8 *)&g.d_006366ac))
#define text_fake_bold (*(int *)((u8 *)&g.d_006366c0))
#define text_shadow_color (*(int *)((u8 *)&g.d_006366b4))
#define text_shadow_dx (*(uint *)((u8 *)&g.d_006366b8))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl text_draw_right_aligned(iptr param_1,iptr param_2,int param_3,i32 param_4,int param_5)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = font_text_width(text_draw_font,param_2);
  if (-1 < text_shadow_color) {
    if ((int)text_shadow_dx < 1) {
      local_8 = local_8 + ~text_shadow_dx + 1;
    }
    else {
      local_8 += text_shadow_dx;
    }
  }
  iVar1 = param_3 + (param_5 - (local_8 + text_fake_bold));
  text_draw_shadowed(param_1,param_2,iVar1,param_4);
  return iVar1;
}
#undef text_draw_font
#undef text_fake_bold
#undef text_shadow_color
#undef text_shadow_dx
#undef local_8

/* 005c5520 auto */
void __cdecl res_free(i32 param_1)

{
  res_free_impl(param_1);
  return;
}

/* 005c5540 auto */
i32 __cdecl res_load(iptr param_1,i32 param_2)

{
  i32 uVar1;
  
  uVar1 = res_load_impl(param_1,param_2);
  return uVar1;
}

/* 005c5560 auto */
i32 __cdecl res_lock(i32 param_1)

{
  i32 uVar1;
  
  uVar1 = res_lock_impl(param_1);
  return uVar1;
}

/* 005c5580 auto */
void __cdecl res_unlock(i32 param_1)

{
  res_unlock_impl(param_1);
  return;
}

/* 005d7c00 auto */
FileObject * __thiscall file_obj_init(FileObject *this)

{
  _memset(this,0,0x98);
  return this;
}

/* 005d7c6e auto */
i32 __thiscall file_obj_close(FileObject *this)

{
  i32 uVar1;
  
  uVar1 = file_map_close(this);
  return uVar1;
}

/* 005d8270 auto */
#define local_108 (*(char (*)[260])(frame_ + FRAME_OFF(0)))
i32 __cdecl file_obj_open_path(char *param_1,iptr param_2)

{
  char *pcVar1;
  HFILE HVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(264)] __attribute__((aligned(8)));  /* original stack frame */
  
  pcVar1 = _strchr(param_1,0x5c);
  if (pcVar1 == (char *)0x0) {
    __getcwd(local_108,0x104);
    FUN_005f22e0(local_108,&file_path_backslash_str);
    FUN_005f22e0(local_108,param_1);
  }
  else {
    FUN_005f22d0(local_108,param_1);
  }
  HVar2 = OpenFile(local_108,(LPOFSTRUCT)(param_2 + 8),0x4000);
  if (HVar2 == -1) {
    uVar3 = 0;
  }
  else {
    HVar2 = OpenFile(local_108,(LPOFSTRUCT)(param_2 + 8),2);
    *(HFILE *)(param_2 + 4) = HVar2;
    if (*(int *)(param_2 + 4) == -1) {
      *(i32 *)param_2 = 0;
      HVar2 = OpenFile(local_108,(LPOFSTRUCT)(param_2 + 8),0);
      *(HFILE *)(param_2 + 4) = HVar2;
      *(i32 *)(param_2 + 0x94) = 0;
      *(i32 *)(param_2 + 0x90) = 0;
      if (*(int *)(param_2 + 4) == -1) {
        *(i32 *)(param_2 + 4) = 0;
        return 0;
      }
    }
    else {
      *(i32 *)param_2 = 1;
    }
    uVar3 = 1;
  }
  return uVar3;
}
#undef local_108

/* 005d83d6 auto */
uint __cdecl file_obj_create_path(LPCSTR param_1,iptr param_2)

{
  HANDLE pvVar1;
  bool bVar2;
  
  pvVar1 = CreateFileA(param_1,0xc0000000,0,(LPSECURITY_ATTRIBUTES)0x0,2,0x80,(HANDLE)0x0);
  *(HANDLE *)(param_2 + 4) = pvVar1;
  bVar2 = *(int *)(param_2 + 4) != -1;
  if (bVar2) {
    *(i32 *)param_2 = 1;
    *(i32 *)(param_2 + 0x94) = 0;
    *(i32 *)(param_2 + 0x90) = 0;
  }
  else {
    *(i32 *)(param_2 + 4) = 0;
    *(i32 *)param_2 = 0;
    *(i32 *)(param_2 + 0x94) = 0;
    *(i32 *)(param_2 + 0x90) = 0;
  }
  return (uint)bVar2;
}

/* 005d8476 auto */
i32 __cdecl file_obj_close_handle(iptr param_1)

{
  i32 uVar1;
  BOOL BVar2;
  
  if (*(int *)(param_1 + 4) == 0) {
    uVar1 = 0;
  }
  else {
    if ((*(int *)(param_1 + 0x94) != 0) || (*(int *)(param_1 + 0x90) != 0)) {
      file_obj_close_mapping(param_1);
    }
    BVar2 = CloseHandle(*(HANDLE *)(param_1 + 4));
    if (BVar2 == 0) {
      uVar1 = 0;
    }
    else {
      *(i32 *)(param_1 + 4) = 0;
      uVar1 = 1;
    }
  }
  return uVar1;
}

/* 005d84f6 auto */
#define local_8 (*(DWORD *)(frame_ + FRAME_OFF(0)))
i32 __cdecl file_obj_read_bytes(iptr param_1,LPVOID param_2,DWORD param_3)

{
  i32 uVar1;
  BOOL BVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(param_1 + 4) == 0) {
    uVar1 = 0;
  }
  else {
    BVar2 = ReadFile(*(HANDLE *)(param_1 + 4),param_2,param_3,&local_8,(LPOVERLAPPED)0x0);
    if (BVar2 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}
#undef local_8

/* 005d8622 auto */
i32 __cdecl file_obj_seek_rel(iptr param_1,LONG param_2)

{
  i32 uVar1;
  DWORD DVar2;
  
  if (*(int *)(param_1 + 4) == 0) {
    uVar1 = 0;
  }
  else {
    DVar2 = SetFilePointer(*(HANDLE *)(param_1 + 4),param_2,(PLONG)0x0,1);
    if (DVar2 == 0xffffffff) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}

/* 005d8721 auto */
#define local_8 (*(DWORD *)(frame_ + FRAME_OFF(0)))
i32 __cdecl file_obj_write_bytes(iptr param_1,iptr param_2,DWORD param_3)

{
  i32 uVar1;
  BOOL BVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(param_1 + 4) == 0) {
    uVar1 = 0;
  }
  else if (*(int *)param_1 == 0) {
    dbg_log(ADDR(0x638640, ((u8 *)&g.d_00638640)));
    uVar1 = 0;
  }
  else {
    BVar2 = WriteFile(*(HANDLE *)(param_1 + 4),(LPCVOID)param_2,param_3,&local_8,(LPOVERLAPPED)0x0);
    if (BVar2 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}
#undef local_8

/* 005d881c auto */
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(DWORD *)(frame_ + FRAME_OFF(8)))
#define local_c (*(char * *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(char (*)[4])(frame_ + FRAME_OFF(16)))
int __cdecl file_obj_read_line_impl(iptr param_1,char *param_2,int param_3)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = 0;
  local_c = param_2;
  *param_2 = '\0';
  if (*(int *)(param_1 + 4) == 0) {
    local_18 = 0;
  }
  else {
    local_18 = ReadFile(*(HANDLE *)(param_1 + 4),local_8,1,&local_10,(LPOVERLAPPED)0x0);
    if (local_10 == 0) {
      local_18 = 0;
    }
    else {
      while (((((local_18 != 0 && (local_10 != 0)) && (local_8[0] != '\n')) &&
              ((local_8[0] != '\r' && (local_8[0] != '\0')))) && (local_14 < param_3))) {
        if (((local_8[0] != '\r') && (local_8[0] != '\n')) && (local_8[0] != '\0')) {
          *local_c = local_8[0];
          local_c++;
          local_14++;
        }
        local_18 = ReadFile(*(HANDLE *)(param_1 + 4),local_8,1,&local_10,(LPOVERLAPPED)0x0);
      }
      *local_c = '\0';
      while (((local_18 != 0 && (local_10 != 0)) && ((local_8[0] == '\n' || (local_8[0] == '\r')))))
      {
        local_18 = ReadFile(*(HANDLE *)(param_1 + 4),local_8,1,&local_10,(LPOVERLAPPED)0x0);
      }
      if (local_10 != 0) {
        file_obj_seek_rel(param_1,0xffffffff);
      }
    }
  }
  return local_18;
}
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005d898e auto */
DWORD __cdecl file_obj_get_size_impl(iptr param_1)

{
  DWORD DVar1;
  
  if (*(int *)(param_1 + 4) == 0) {
    DVar1 = 0;
  }
  else {
    DVar1 = GetFileSize(*(HANDLE *)(param_1 + 4),(LPDWORD)0x0);
    if (DVar1 == 0xffffffff) {
      dbg_log(ADDR(0x63869c, ((u8 *)&g.d_0063869c)));
      DVar1 = 0;
    }
  }
  return DVar1;
}

/* 005d8ab8 auto */
i32 __cdecl file_obj_close_mapping(iptr param_1)

{
  if ((*(int *)(param_1 + 0x94) != 0) && (*(int *)(param_1 + 0x90) != 0)) {
    UnmapViewOfFile(*(LPCVOID *)(param_1 + 0x90));
    *(i32 *)(param_1 + 0x90) = 0;
  }
  if (*(int *)(param_1 + 0x94) != 0) {
    CloseHandle(*(HANDLE *)(param_1 + 0x94));
    *(i32 *)(param_1 + 0x94) = 0;
  }
  return 0;
}

/* 005db140 auto */
#define res_dll_module_count (*(int *)((u8 *)&g.d_006387cc))
#define local_84 (*(i8 (*)[128])(frame_ + FRAME_OFF(4)))
HMODULE __cdecl res_dll_load_library(LPCSTR param_1)

{
  HMODULE pHVar1;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  pHVar1 = LoadLibraryExA(param_1,(HANDLE)0x0,2);
  if (pHVar1 == (HMODULE)0x0) {
    FUN_005f22d0(local_84,s_Error__Resource_file_006387d0);
    FUN_005f22e0(local_84,param_1);
    FUN_005f22e0(local_84,s_not_found__006387e8);
    dbg_log((iptr)local_84);
    pHVar1 = (HMODULE)0x0;
  }
  else {
    *(HMODULE *)(&res_dll_modules + res_dll_module_count * 4) = pHVar1;
    res_dll_module_count++;
  }
  return pHVar1;
}
#undef res_dll_module_count
#undef local_84

/* 005db1e0 auto */
void __cdecl res_free_impl(HGLOBAL param_1)

{
  FreeResource(param_1);
  return;
}

/* 005db1fa auto */
#define app_hinstance (*(HMODULE *)((u8 *)&g.d_006e4ff0))
#define res_dll_module_count (*(uint *)((u8 *)&g.d_006387cc))
#define local_1c (*(HMODULE *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(HRSRC *)(frame_ + FRAME_OFF(16)))
#define local_c (*(CHAR *)(frame_ + FRAME_OFF(20)))
#define local_b (*(CHAR *)(frame_ + FRAME_OFF(21)))
#define local_a (*(CHAR *)(frame_ + FRAME_OFF(22)))
#define local_9 (*(CHAR *)(frame_ + FRAME_OFF(23)))
#define local_8 (*(i8 *)(frame_ + FRAME_OFF(24)))
HGLOBAL __cdecl res_load_impl(CHAR *param_1,LPCSTR param_2)

{
  HGLOBAL pvVar1;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = *param_1;
  local_b = param_1[1];
  local_a = param_1[2];
  local_9 = param_1[3];
  local_8 = 0;
  local_14 = 0xffffffff;
  local_10 = FindResourceA(app_hinstance,param_2,&local_c);
  if (local_10 == (HRSRC)0x0) {
    local_14 = 0;
    while ((local_14 < res_dll_module_count &&
           (local_10 = FindResourceA(*(HMODULE *)(&res_dll_modules + local_14 * 4),param_2,&local_c),
           local_10 == (HRSRC)0x0))) {
      local_14++;
    }
  }
  if (local_10 == (HRSRC)0x0) {
    pvVar1 = (HGLOBAL)0x0;
  }
  else {
    if (local_14 == 0xffffffff) {
      local_1c = app_hinstance;
    }
    else {
      local_1c = *(HMODULE *)(&res_dll_modules + local_14 * 4);
    }
    pvVar1 = LoadResource(local_1c,local_10);
  }
  return pvVar1;
}
#undef app_hinstance
#undef res_dll_module_count
#undef local_1c
#undef local_14
#undef local_10
#undef local_c
#undef local_b
#undef local_a
#undef local_9
#undef local_8

/* 005db531 auto */
LPVOID __cdecl res_lock_impl(HGLOBAL param_1)

{
  LPVOID pvVar1;
  
  pvVar1 = LockResource(param_1);
  return pvVar1;
}

/* 005db54b auto */
void __cdecl res_unlock_impl(i32 param_1)

{
  return;
}

/* 005db55b auto */
#define res_dll_module_count (*(uint *)((u8 *)&g.d_006387cc))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
void __cdecl dll_unload(HMODULE param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0;
      (*(HMODULE *)(&res_dll_modules + local_8 * 4) != param_1 && (local_8 < res_dll_module_count));
      local_8 = local_8 + 1) {
  }
  if (local_8 < res_dll_module_count) {
    for (; local_8 < res_dll_module_count; local_8++) {
      *(i32 *)(&res_dll_modules + local_8 * 4) = *(i32 *)(&res_dll_modules_elem1 + local_8 * 4);
    }
    res_dll_module_count--;
    FreeLibrary(param_1);
  }
  return;
}
#undef res_dll_module_count
#undef local_8
