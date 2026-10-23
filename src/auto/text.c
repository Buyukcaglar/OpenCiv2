/* The game, text: game text files, strings, resources and files: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 0040bbb0 auto */
void __cdecl text_clear(void)

{
  str_clear((iptr)((u8 *)&g.d_00679640));
  return;
}

/* 0040bbe0 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
void __cdecl text_append(iptr str)

{
  crt_strcat(&text_buffer,str);
  return;
}
#undef text_buffer

/* 0040bc10 auto */
void __cdecl text_append_label(i32 label_id)

{
  str_append_label((iptr)((u8 *)&g.d_00679640),label_id);
  return;
}

/* 0040fe10 auto */
void __cdecl text_append_space(void)

{
  str_append_space((iptr)((u8 *)&g.d_00679640));
  return;
}

/* 0040fe40 auto */
void __cdecl text_append_colon(void)

{
  str_append_colon((iptr)((u8 *)&g.d_00679640));
  return;
}

/* 0040fe70 auto */
void __cdecl text_append_percent(void)

{
  str_append_percent((iptr)((u8 *)&g.d_00679640));
  return;
}

/* 0040fea0 auto */
void __cdecl text_append_lparen(void)

{
  str_append_lparen((iptr)((u8 *)&g.d_00679640));
  return;
}

/* 0040fed0 auto */
void __cdecl text_append_rparen(void)

{
  str_append_rparen((iptr)((u8 *)&g.d_00679640));
  return;
}

/* 0040ff00 auto */
void __cdecl text_append_string_id(i32 string_id)

{
  str_append_string_id((iptr)((u8 *)&g.d_00679640),string_id);
  return;
}

/* 0040ff30 auto */
void __cdecl text_append_int(iptr value)

{
  str_append_int((iptr)((u8 *)&g.d_00679640),value);
  return;
}

/* 0040ff60 auto */
i32 __cdecl text_set_string_arg(iptr index,iptr str)

{
  i32 result;
  
  result = crt_strcpy(&text_string_args + index * 0x104,str);
  return result;
}

/* 00414d70 auto */
void __cdecl text_append_str(iptr str)

{
  str_concat((iptr)((u8 *)&g.d_00679640),str);
  return;
}

/* 00415040 auto */
iptr __cdecl file_build_open_path(iptr dest,i32 name2)

{
  if (file_path_mode == '\0') {
    crt_strcpy(dest,name2);
  }
  else {
    path_join_upper(dest,(iptr)((u8 *)&g.d_006250d8),name2);
  }
  return dest;
}

/* 0041508c auto */
#define error_last_open_failed (*(uint *)((u8 *)&g.d_00634810))
#define path (*(char (*)[136])(frame_ + FRAME_OFF(4)))
FILE * __cdecl file_open_path(iptr name2,iptr mode)

{
  FILE *pFVar1;
  i8 frame_[FRAME_OFF(144)] __attribute__((aligned(8)));  /* original stack frame */
  
  file_build_open_path((iptr)path,name2);
  crt_strcpy(&error_last_open_path,path);
  pFVar1 = _fopen(path,(char *)mode);
  error_last_open_failed = (uint)(pFVar1 == (FILE *)0x0);
  return pFVar1;
}
#undef error_last_open_failed
#undef path

/* 00415133 auto */
#define exists (*(i32 *)(frame_ + FRAME_OFF(0)))
uint __cdecl file_exists(iptr name2)

{
  FILE *_File;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  _File = (FILE *)file_open_path(name2,(iptr)((u8 *)&g.d_00625118));
  if (_File != (FILE *)0x0) {
    _fclose(_File);
  }
  exists = (uint)(_File != (FILE *)0x0);
  return exists;
}
#undef exists

/* 004190a0 auto */
void __cdecl text_append_spaces(i32 count)

{
  str_append_spaces((iptr)((u8 *)&g.d_00679640),count);
  return;
}

/* 0041e7e3 auto */
void __cdecl labels_reload(void)

{
  int value;
  
  value = text_open_section((iptr)PTR_s_LABELS_00627674,(iptr)((u8 *)&g.d_00625618));
  if (value == 0) {
    text_read_line(1);
    value = text_next_int();
    if (strpool_capacity < value) {
      strpool_capacity = value;
    }
  }
  strpool_init(strpool_capacity);
  strpool_add((iptr)((u8 *)&g.d_00625624));
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

i32 __thiscall file_obj_create(FileObject *this,iptr path)

{
  i32 result;
  
  result = file_obj_create_path(path,(iptr)this);
  return result;
}

/* 00421c30 auto */
i32 __thiscall file_map_close(FileObject *this)

{
  i32 result;
  
  result = file_obj_close_handle((iptr)this);
  return result;
}

/* 00421c60 auto */
void __thiscall file_obj_write(FileObject *this,iptr data,i32 size)

{
  file_obj_write_bytes((iptr)this,data,size);
  return;
}

/* 00421d30 auto */
void __cdecl text_append_comma(void)

{
  str_append_comma((iptr)((u8 *)&g.d_00679640));
  return;
}

/* 00421d60 auto */
i32 __cdecl text_set_string_arg_b(int index,iptr text)

{
  i32 result;
  
  result = crt_strcpy(&text_string_args + index * 0x104,text);
  return result;
}

/* 00421da0 auto */
i32 __cdecl text_set_number_arg(int index,i32 value)

{
  *(i32 *)(&text_number_args + index * 4) = value;
  return value;
}

/* 00421f10 auto */
void __cdecl text_append_year(i32 year)

{
  str_append_year((iptr)((u8 *)&g.d_00679640),year);
  return;
}

/* 00426ff0 auto */
#define tag (*(char * *)(frame_ + FRAME_OFF(4)))
#define pad_i (*(uint *)(frame_ + FRAME_OFF(8)))
#define num_buf (*(char (*)[40])(frame_ + FRAME_OFF(12)))
void __cdecl text_expand_vars(iptr src,iptr dest)

{
  char *percent_pos;
  int arg_index;
  size_t len;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i8 *)dest = 0;
  do {
    percent_pos = _strchr((char *)src,0x25);
    if (percent_pos != (char *)0x0) {
      *percent_pos = '\0';
    }
    if (*(char *)src != '\0') {
      crt_strcat(dest,src);
    }
    tag = percent_pos;
    if (percent_pos != (char *)0x0) {
      tag = percent_pos + 1;
      arg_index = __strnicmp(tag,s_STRING_00625e40,6);
      if (arg_index == 0) {
        arg_index = _atoi(percent_pos + 7);
        crt_strcat(dest,&text_string_args + arg_index * 0x104);
        src = (iptr)(percent_pos + 8);
        if (9 < arg_index) {
          src = (iptr)(percent_pos + 9);
        }
      }
      else {
        arg_index = _strncmp(tag,s_NUMBER_00625e48,6);
        if (arg_index == 0) {
          arg_index = _atoi(percent_pos + 7);
          __ltoa(*(long *)(&text_number_args + arg_index * 4),num_buf,10);
          crt_strcat(dest,num_buf);
          src = (iptr)(percent_pos + 8);
        }
        else {
          arg_index = _strncmp(tag,&text_var_hex_tag_str,3);
          if (arg_index == 0) {
            arg_index = _atoi(percent_pos + 4);
            __ltoa(*(long *)(&text_number_args + arg_index * 4),num_buf,0x10);
            for (pad_i = 0; len = _strlen(num_buf), pad_i < 4 - len;
                pad_i = pad_i + 1) {
              crt_strcat(dest,&text_var_hex_pad_str);
            }
            crt_strcat(dest,num_buf);
            src = (iptr)(percent_pos + 5);
          }
          else {
            src = (iptr)tag;
            if (*tag == '%') {
              crt_strcat(dest,&text_var_percent_str);
              src = (iptr)(percent_pos + 2);
            }
          }
        }
      }
    }
  } while (tag != (char *)0x0);
  return;
}
#undef tag
#undef pad_i
#undef num_buf

/* 004271e8 auto */
i32 __cdecl text_set_label_arg(i32 index,i32 label_id)

{
  iptr label_text;
  i32 result;
  
  label_text = label_string(label_id);
  result = text_set_string_arg_b(index,label_text);
  return result;
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
void __cdecl strpool_init(uint pool_size)

{
  if (strpool_initialized == 0) {
    strpool_initialized = 1;
    memblock_init((iptr)((u8 *)&g.d_0063e4c0),2,pool_size);
  }
  else {
    memblock_free((iptr)((u8 *)&g.d_0063e4c0));
    memblock_init((iptr)((u8 *)&g.d_0063e4c0),2,pool_size);
  }
  strpool_count = 0;
  return;
}
#undef strpool_count

/* 00428a78 auto */
void __cdecl strpool_free(void)

{
  memblock_free((iptr)((u8 *)&g.d_0063e4c0));
  return;
}

/* 00428a95 auto */
#define strpool_count (*(int *)((u8 *)&g.d_00625e60))
#define strpool_last_string (*(i32 *)((u8 *)&g.d_0063e4b8))
int __cdecl strpool_add(iptr text)

{
  size_t len;
  int string_id;
  
  len = _strlen((char *)text);
  if (len == 0) {
    string_id = 0;
  }
  else {
    len = _strlen((char *)text);
    strpool_last_string = memblock_alloc((iptr)((u8 *)&g.d_0063e4c0),len + 1);
    crt_strcpy(strpool_last_string,text);
    string_id = strpool_count;
    strpool_count++;
  }
  return string_id;
}
#undef strpool_count
#undef strpool_last_string

/* 00428b0c auto */
#define cursor (*(char * *)(frame_ + FRAME_OFF(0)))
char * __cdecl label_string(int index)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  cursor = strpool_data;
  for (; index != 0; index--) {
    for (; *cursor != '\0'; cursor++) {
    }
    for (; *cursor == '\0'; cursor++) {
    }
  }
  return cursor;
}
#undef cursor

/* 00428b68 auto */
#define strpool_count (*(int *)((u8 *)&g.d_00625e60))
#define strpool_last_string (*(char * *)((u8 *)&g.d_0063e4b8))
#define alloc_size (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl strpool_add_padded(iptr text,uint min_size)

{
  int string_id;
  size_t len;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  len = _strlen((char *)text);
  if ((int)min_size < (int)(len + 1)) {
    len = _strlen((char *)text);
    alloc_size = len + 1;
  }
  else {
    alloc_size = min_size;
  }
  strpool_last_string = (char *)memblock_alloc((iptr)((u8 *)&g.d_0063e4c0),alloc_size);
  _memset(strpool_last_string,0,alloc_size);
  _strncpy(strpool_last_string,(char *)text,alloc_size);
  len = _strlen((char *)text);
  if (len == 0) {
    *strpool_last_string = ' ';
  }
  string_id = strpool_count;
  strpool_count++;
  return string_id;
}
#undef strpool_count
#undef strpool_last_string
#undef alloc_size

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
  str_append_period((iptr)((u8 *)&g.d_00679640));
  return;
}

/* 0043c840 auto */
void __cdecl str_append(iptr dest,iptr src)

{
  crt_strcat(dest,src);
  return;
}

/* 0043c870 auto */
void __cdecl text_append_long(i32 value)

{
  str_append_long((iptr)((u8 *)&g.d_00679640),value);
  return;
}

/* 0043c8a0 auto */
void __cdecl text_append_gold(i32 gold)

{
  str_append_gold((iptr)((u8 *)&g.d_00679640),gold);
  return;
}

/* 0043ca50 auto */
void __cdecl text_append_population(iptr civ,i32 population)

{
  str_append_population((iptr)((u8 *)&g.d_00679640),civ,population);
  return;
}

/* 0043ca80 auto */
void __cdecl text_append_city_name(iptr city)

{
  str_append_city_name((iptr)((u8 *)&g.d_00679640),city);
  return;
}

/* 0043cda6 auto */
#define pop (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl str_append_population(iptr dest,iptr civ,int population)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (population < 0) {
    pop = civ_total_population(civ);
  }
  else {
    pop = population;
  }
  if (99 < pop) {
    str_append_int(dest,pop / 100);
    crt_strcat(dest,&pop_thousands_sep_str);
    pop = pop % 100;
    if (pop < 10) {
      crt_strcat(dest,&pop_zero_pad_str);
    }
  }
  str_append_int(dest,pop);
  crt_strcat(dest,s_0_000_00626240);
  return;
}
#undef pop

/* 0043ce5a auto */
#define pop (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl str_append_city_population(iptr dest,iptr city)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  pop = city_population_units(city);
  if (99 < pop) {
    str_append_int(dest,pop / 100);
    crt_strcat(dest,&city_pop_thousands_sep_str);
    pop = pop % 100;
    if (pop < 10) {
      crt_strcat(dest,&city_pop_zero_pad_str);
    }
  }
  str_append_int(dest,pop);
  crt_strcat(dest,s_0_000_00626250);
  return;
}
#undef pop

/* 0043f444 auto */
void __cdecl str_append_city_name(iptr dest,int city)

{
  if (city < 0) {
    str_append_label(dest,0xe);
  }
  else {
    str_concat(dest,(iptr)&cities[city].name);
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
void __thiscall dll_handle_load(DllHandle *this,iptr path)

{
  u32 module;
  
  if (this->hmodule != 0) {
    dll_unload(this->hmodule);
  }
  module = res_dll_load_library(path);
  this->hmodule = module;
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
void __cdecl text_set_number_arg_v(int index,i32 value)

{
  *(i32 *)(&text_number_args + index * 4) = value;
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
#define saved_dir (*(i8 (*)[260])(frame_ + FRAME_OFF(0)))
#define i (*(int *)(frame_ + FRAME_OFF(260)))
#define result (*(int *)(frame_ + FRAME_OFF(264)))
int __cdecl labels_load(void)

{
  int status;
  i32 string_id;
  i8 frame_[FRAME_OFF(272)] __attribute__((aligned(8)));  /* original stack frame */
  
  result = -1;
  status = text_open_section((iptr)((u8 *)&g.d_00628430),(iptr)((u8 *)&g.d_00628428));
  if (status == 0) {
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
        for (i = 0; i < label_count; i++) {
          string_id = text_read_line_pooled();
          *(i32 *)(label_string_ids + i * 4) = string_id;
        }
        if (i < 0x378) {
          crt_strcpy(saved_dir,&scenario_dir_path);
          crt_strcpy(&scenario_dir_path,&game_home_dir);
          status = text_open_section((iptr)((u8 *)&g.d_00628440),(iptr)((u8 *)&g.d_00628438));
          if (status == 0) {
            text_read_line(1);
            status = text_next_int();
            for (i = 0; i < label_count; i++) {
              text_read_line(1);
            }
            for (; i < status; i++) {
              string_id = text_read_line_pooled();
              *(i32 *)(label_string_ids + i * 4) = string_id;
            }
          }
          crt_strcpy(&scenario_dir_path,saved_dir);
          if (i < 0x378) {
            string_id = strpool_add((iptr)((u8 *)&g.d_00628448));
            for (; i < 0x378; i++) {
              *(i32 *)(label_string_ids + i * 4) = string_id;
            }
          }
        }
        result = i;
      }
    }
  }
  else {
    error_report(0xfffffff8,4,0,0,0);
  }
  text_close_file();
  if (result < 1) {
    labels_free();
  }
  return result;
}
#undef label_count
#undef label_ids_handle
#undef saved_dir
#undef i
#undef result

/* 0046e8f0 auto */
#define value (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl str_parse_hex(iptr text)

{
  char ch;
  int _C;
  int is_digit;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  value = 0;
  while (*(char *)text != '\0') {
    ch = *(char *)text;
    text++;
    _C = crt_toupper((int)ch);
    is_digit = _isdigit(_C);
    if (is_digit == 0) {
      if ((_C < 0x41) || (0x46 < _C)) {
        for (; *(char *)text != '\0'; text++) {
        }
      }
      else {
        value = value * 0x10 + _C - 0x37;
      }
    }
    else {
      value = value * 0x10 + _C - 0x30;
    }
  }
  return value;
}
#undef value

/* 00485208 auto */
#define scenario_year_increment (*(short *)((u8 *)&g.d_0064bcb4))
#define abs_year (*(uint *)(frame_ + FRAME_OFF(4)))
#define abs_years (*(int *)(frame_ + FRAME_OFF(8)))
#define month_neg (*(int *)(frame_ + FRAME_OFF(12)))
#define month_pos (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl str_append_year(iptr dest,uint year)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((game.game_flags & 0x80) == 0) || (-1 < scenario_year_increment)) {
    if ((-1 < (int)year) && (game_language == 0)) {
      str_append_label(dest,1);
      str_append_space(dest);
    }
    if ((int)year < 1) {
      abs_year = ~year + 1;
    }
    else {
      abs_year = year;
    }
    str_append_int(dest,abs_year);
    if ((-1 < (int)year) && (game_language != 0)) {
      str_append_space(dest);
      str_append_label(dest,1);
    }
    if ((int)year < 0) {
      str_append_space(dest);
      str_append_label(dest,0);
    }
  }
  else {
    if ((int)year < 1) {
      if ((int)year % 0xc < 1) {
        month_neg = ~((int)year % 0xc) + 1;
      }
      else {
        month_neg = (int)year % 0xc;
      }
      text_append_label(0x1af - month_neg);
    }
    else {
      if ((int)year % 0xc < 1) {
        month_pos = ~((int)year % 0xc) + 1;
      }
      else {
        month_pos = (int)year % 0xc;
      }
      text_append_label(month_pos + 0x1a4);
    }
    text_append_space();
    if ((int)year / 0xc < 1) {
      abs_years = ~((int)year / 0xc) + 1;
    }
    else {
      abs_years = (int)year / 0xc;
    }
    str_append_int(dest,abs_years);
  }
  return;
}
#undef scenario_year_increment
#undef abs_year
#undef abs_years
#undef month_neg
#undef month_pos

/* 004929c0 auto */
/* Library Function - Multiple Matches With Same Base Name
    protected: virtual unsigned char * __thiscall CHtmlStream::Realloc(unsigned char *,unsigned
   long)
    protected: virtual unsigned char * __thiscall CMemFile::Realloc(unsigned char *,unsigned long)
   
   Library: Visual Studio 1998 Debug */

i32 __thiscall file_obj_open(FileObject *this,iptr path)

{
  i32 result;
  
  result = file_obj_open_path(path,(iptr)this);
  return result;
}

/* 00492a00 auto */
/* Library Function - Multiple Matches With Same Base Name
    protected: virtual unsigned char * __thiscall CHtmlStream::Realloc(unsigned char *,unsigned
   long)
    protected: virtual unsigned char * __thiscall CMemFile::Realloc(unsigned char *,unsigned long)
   
   Library: Visual Studio 1998 Debug */

i32 __thiscall file_obj_seek_cur(FileSeekView *this,i32 offset)

{
  i32 result;
  
  result = file_obj_seek_rel((iptr)this,offset);
  return result;
}

/* 00492a40 auto */
void __thiscall file_obj_read_line(FileReadLineView *this,iptr buf,i32 max_len)

{
  file_obj_read_line_impl((iptr)this,buf,max_len);
  return;
}

/* 00492a80 auto */
i32 __thiscall file_obj_get_size(FileObject *this)

{
  i32 size;
  
  size = file_obj_get_size_impl((iptr)this);
  return size;
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
#define section_tag (*(char (*)[80])(frame_ + FRAME_OFF(4)))
#define result (*(int *)(frame_ + FRAME_OFF(84)))
#define name2 (*(char (*)[260])(frame_ + FRAME_OFF(88)))
#define saved_cwd (*(char (*)[260])(frame_ + FRAME_OFF(348)))
#define section_offset (*(int *)(frame_ + FRAME_OFF(608)))
int __cdecl text_open_file_section(int filename,int section)

{
  bool found;
  bool allow_rewind;
  size_t len;
  char *line;
  int cmp;
  i8 frame_[FRAME_OFF(616)] __attribute__((aligned(8)));  /* original stack frame */
  
  result = 1;
  allow_rewind = false;
  section_offset = -1;
  str_clear((iptr)name2);
  str_clear((iptr)section_tag);
  if (section != 0) {
    section_tag[0] = '@';
    section_tag[1] = 0;
    crt_strcat(section_tag,section);
    __strupr(section_tag);
  }
  if (filename == 0) {
    allow_rewind = true;
  }
  else {
    text_close_file();
    crt_strcpy(name2,filename);
    path_default_extension((iptr)name2,(iptr)((u8 *)&g.d_0062cd24));
    __getcwd(saved_cwd,0x104);
    __chdir(&scenario_dir_path);
    text_file_handle = (FILE *)file_open_path((iptr)name2,(iptr)((u8 *)&g.d_0062cd28));
    if ((text_file_handle != (FILE *)0x0) && (len = _strlen(name2), len != 0)) {
      section_offset = text_section_index_lookup((iptr)name2,(iptr)section_tag);
    }
    __chdir(&game_home_dir);
    if (((text_file_handle == (FILE *)0x0) &&
        (text_file_handle = (FILE *)file_open_path((iptr)name2,(iptr)((u8 *)&g.d_0062cd2c)),
        text_file_handle != (FILE *)0x0)) && (len = _strlen(name2), len != 0)) {
      section_offset = text_section_index_lookup((iptr)name2,(iptr)section_tag);
    }
    __chdir(saved_cwd);
    if (text_file_handle == (FILE *)0x0) goto LAB_004a2348;
  }
  if (section == 0) {
    result = 0;
  }
  else {
    if (0 < section_offset) {
      _fseek(text_file_handle,section_offset,0);
    }
    found = false;
    while (!found) {
      if ((CRT_FEOF(text_file_handle)) != 0) {
        if (!allow_rewind) goto LAB_004a2348;
        allow_rewind = false;
        _rewind(text_file_handle);
      }
      line = _fgets(&text_buffer,0xff,text_file_handle);
      if (line != (char *)0x0) {
        str_strip_newline((iptr)((u8 *)&g.d_00679640));
        str_trim((iptr)((u8 *)&g.d_00679640));
        cmp = __strcmpi(&text_buffer,section_tag);
        if (cmp == 0) {
          found = true;
        }
      }
    }
    len = _strlen(&text_buffer);
    text_line_cursor = &text_buffer + len;
    result = 0;
  }
LAB_004a2348:
  if (result != 0) {
    text_close_file();
  }
  return result;
}
#undef text_buffer
#undef text_file_handle
#undef text_line_cursor
#undef section_tag
#undef result
#undef name2
#undef saved_cwd
#undef section_offset

/* 004a2379 auto */
#define saved_dir (*(i8 (*)[260])(frame_ + FRAME_OFF(4)))
#define result (*(int *)(frame_ + FRAME_OFF(264)))
int __cdecl text_open_section(iptr filename,iptr section)

{
  i8 frame_[FRAME_OFF(272)] __attribute__((aligned(8)));  /* original stack frame */
  
  result = text_open_file_section(filename,section);
  if (result != 0) {
    crt_strcpy(saved_dir,&scenario_dir_path);
    crt_strcpy(&scenario_dir_path,&game_home_dir);
    result = text_open_file_section(filename,section);
    crt_strcpy(&scenario_dir_path,saved_dir);
  }
  return result;
}
#undef saved_dir
#undef result

/* 004a23fc auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define text_file_handle (*(FILE * *)((u8 *)&g.d_0062cd20))
#define text_line_cursor (*(i8 * *)((u8 *)&g.d_00673f14))
#define result (*(i8 * *)(frame_ + FRAME_OFF(0)))
i8 * __cdecl text_read_line(int trim)

{
  char *line;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  result = (i8 *)0x0;
  if (((CRT_FEOF(text_file_handle)) == 0) &&
     (line = _fgets(&text_buffer,0xff,text_file_handle), line != (char *)0x0)) {
    str_strip_newline((iptr)((u8 *)&g.d_00679640));
    if (trim == 1) {
      str_trim((iptr)((u8 *)&g.d_00679640));
    }
    text_line_cursor = &text_buffer;
    result = &text_buffer;
  }
  if (result == (i8 *)0x0) {
    text_buffer = 0;
    text_close_file();
  }
  return result;
}
#undef text_buffer
#undef text_file_handle
#undef text_line_cursor
#undef result

/* 004a24b1 auto */
#define text_line_cursor (*(char * *)((u8 *)&g.d_00673f14))
#define text_token_buf (*(i8 *)((u8 *)&g.d_00673e10))
#define dest (*(char * *)(frame_ + FRAME_OFF(0)))
i8 * __cdecl text_next_token(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  dest = &text_token_buf;
  for (; (*text_line_cursor != '\0' && (*text_line_cursor != ',')); text_line_cursor++) {
    *dest = *text_line_cursor;
    dest++;
  }
  if (*text_line_cursor != '\0') {
    text_line_cursor++;
  }
  *dest = '\0';
  str_trim((iptr)((u8 *)&g.d_00673e10));
  return &text_token_buf;
}
#undef text_line_cursor
#undef text_token_buf
#undef dest

/* 004a2534 auto */
i32 __cdecl text_next_int(void)

{
  iptr token;
  i32 value;
  
  token = text_next_token();
  value = str_parse_int_prefixed(token);
  return value;
}

/* 004a257a auto */
i32 __cdecl text_read_line_pooled(void)

{
  i32 string_id;
  
  text_read_line(1);
  string_id = strpool_add((iptr)((u8 *)&g.d_00679640));
  return string_id;
}

/* 004a25aa auto */
i32 __cdecl text_next_token_pooled(void)

{
  i32 string_id;
  
  text_next_token();
  string_id = strpool_add((iptr)((u8 *)&g.d_00673e10));
  return string_id;
}

/* 004a25d5 auto */
#define text_token_buf (*(i8 *)((u8 *)&g.d_00673e10))
#define cursor (*(char * *)(frame_ + FRAME_OFF(4)))
short __cdecl text_next_binary(void)

{
  short value;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  value = 0;
  text_next_token();
  for (cursor = &text_token_buf; (*cursor == '0' || (*cursor == '1')); cursor++) {
    value = value * 2;
    if (*cursor == '1') {
      value++;
    }
  }
  return value;
}
#undef text_token_buf
#undef cursor

/* 004a2645 auto */
#define result (*(i32 *)(frame_ + FRAME_OFF(4)))
#define i (*(int *)(frame_ + FRAME_OFF(8)))
i32 __cdecl text_read_section_line(iptr filename,iptr section,iptr line_index)

{
  int status;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  result = 1;
  status = text_open_section(filename,section);
  if (status == 0) {
    for (i = 0; i <= line_index; i++) {
      text_read_line(1);
    }
    result = 0;
  }
  text_close_file();
  return result;
}
#undef result
#undef i

/* 004a26bf auto */
i32 __cdecl text_next_token_str_id(i32 min_size)

{
  i32 string_id;
  
  text_next_token();
  string_id = strpool_add_padded((iptr)((u8 *)&g.d_00673e10),min_size);
  return string_id;
}

/* 004aef20 auto */
iptr __cdecl str_clear(iptr str)

{
  *(i8 *)str = 0;
  return str;
}

/* 004aef36 auto */
void __cdecl str_append_space(iptr dest)

{
  crt_strcat(dest,&append_space_str);
  return;
}

/* 004aef57 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl str_append_spaces(iptr dest,int count)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (i = 0; i < count; i++) {
    str_append_space(dest);
  }
  return;
}
#undef i

/* 004aef96 auto */
void __cdecl str_append_comma(iptr dest)

{
  crt_strcat(dest,&append_comma_str);
  return;
}

/* 004aefb7 auto */
void __cdecl str_append_colon(iptr dest)

{
  crt_strcat(dest,&append_colon_str);
  return;
}

/* 004aefd8 auto */
void __cdecl str_append_period(iptr dest)

{
  crt_strcat(dest,&append_period_str);
  return;
}

/* 004aeff9 auto */
void __cdecl str_append_percent(iptr dest)

{
  crt_strcat(dest,&append_percent_str);
  return;
}

/* 004af01a auto */
void __cdecl str_append_lparen(iptr dest)

{
  crt_strcat(dest,&append_lparen_str);
  return;
}

/* 004af03b auto */
void __cdecl str_append_rparen(iptr dest)

{
  crt_strcat(dest,&append_rparen_str);
  return;
}

/* 004af09e auto */
void __cdecl str_append_plus(iptr dest)

{
  crt_strcat(dest,&append_plus_str);
  return;
}

/* 004af122 auto */
void __cdecl str_append_string_id(iptr dest,i32 string_id)

{
  i32 text;
  
  text = label_string(string_id);
  crt_strcat(dest,text);
  return;
}

/* 004af14b auto */
void __cdecl str_append_label(iptr dest,int label_id)

{
  str_append_string_id(dest,*(i32 *)(label_string_ids + label_id * 4));
  return;
}

/* 004af174 auto */
void __cdecl str_concat(iptr dest,iptr src)

{
  crt_strcat(dest,src);
  return;
}

/* 004af1d5 auto */
#define num_buf (*(char (*)[20])(frame_ + FRAME_OFF(0)))
i32 __cdecl str_append_int(iptr dest,int value)

{
  i32 result;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  __itoa(value,num_buf,10);
  result = crt_strcat(dest,num_buf);
  return result;
}
#undef num_buf

/* 004af284 auto */
#define num_buf (*(char (*)[20])(frame_ + FRAME_OFF(0)))
void __cdecl str_append_long(iptr dest,long value)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  __ltoa(value,num_buf,10);
  crt_strcat(dest,num_buf);
  return;
}
#undef num_buf

/* 004af2b9 auto */
void __cdecl str_append_gold(iptr dest,i32 gold)

{
  str_append_long(dest,gold);
  text_append_space();
  text_append_label(0x143);
  return;
}

/* 004bb370 auto */
void __thiscall file_obj_read(FileObject *this,iptr buf,i32 size)

{
  file_obj_read_bytes((iptr)this,buf,size);
  return;
}

/* 004befd1 auto */
void __cdecl text_list_append_wrapped(iptr dialog,i32 string_id,iptr item_count,iptr line_count)

{
  if (*(int *)item_count == 0) {
    text_append_lparen();
  }
  else {
    text_append((iptr)((u8 *)&g.d_0062db88));
    if (*(int *)line_count < 4) {
      text_append((iptr)((u8 *)&g.d_0062db8c));
    }
    else {
      *(i32 *)line_count = 0;
      dialog_add_line
                ((DialogAddLineView *)dialog,(iptr)((u8 *)&g.d_00679640),0xffffffff,0xffffffff,0xffffffff,0);
      text_clear();
    }
  }
  *(int *)line_count = *(int *)line_count + 1;
  *(int *)item_count = *(int *)item_count + 1;
  text_append_string_id(string_id);
  return;
}

/* 004c4210 auto */
void __cdecl text_set_number_arg_u8(int index,uint value)

{
  *(uint *)(&text_number_args + index * 4) = value & 0xff;
  return;
}

/* 004ccdb6 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define num_buf (*(char (*)[20])(frame_ + FRAME_OFF(0)))
void __cdecl text_append_int_2d(i32 value)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  _sprintf(num_buf,&int_2d_fmt,value);
  crt_strcat(&text_buffer,num_buf);
  return;
}
#undef text_buffer
#undef num_buf

/* 004ccdef auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define len (*(size_t *)(frame_ + FRAME_OFF(0)))
void __cdecl text_append_advance_abbrev(iptr advance,int with_comma)

{
  size_t abbrev_len;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (advance == -2) {
    crt_strcat(&text_buffer,&advance_abbrev_no_strs + ((with_comma != 0) - 1 & 8));
  }
  else if (advance == -1) {
    crt_strcat(&text_buffer,&advance_abbrev_nil_strs + ((with_comma != 0) - 1 & 8));
  }
  else if (advance < 100) {
    crt_strcat(&text_buffer,advances + advance);
    if (with_comma != 0) {
      crt_strcat(&text_buffer,&advance_abbrev_comma_str);
    }
    abbrev_len = _strlen(advances[advance].abbrev);
    if (abbrev_len < 3) {
      len = _strlen(advances[advance].abbrev);
    }
    else {
      len = 3;
    }
    text_append_spaces(3 - len);
  }
  else {
    crt_strcat(&text_buffer,&advance_abbrev_err_strs + ((with_comma != 0) - 1 & 8));
  }
  return;
}
#undef text_buffer
#undef len

/* 004cfff0 auto */
#define cursor (*(char * *)(frame_ + FRAME_OFF(0)))
void __cdecl str_trim_trailing(iptr str)

{
  uptr len;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  len = _strlen((char *)str);
  if (len != 0) {
    for (cursor = (char *)((len - 1) + str);
        ((uint)str <= cursor &&
        (((*cursor == ' ' || (*cursor == '\t')) && (*cursor = '\0', cursor != (char *)str)))
        ); cursor--) {
    }
  }
  return;
}
#undef cursor

/* 004d007e auto */
#define start (*(char * *)(frame_ + FRAME_OFF(0)))
#define buf (*(i8 (*)[256])(frame_ + FRAME_OFF(4)))
void __cdecl str_trim(iptr str)

{
  i8 frame_[FRAME_OFF(264)] __attribute__((aligned(8)));  /* original stack frame */
  
  str_trim_trailing(str);
  for (start = (char *)str;
      (*start != '\0' && ((*start == ' ' || (*start == '\t'))));
      start = start + 1) {
  }
  crt_strcpy(buf,start);
  crt_strcpy(str,buf);
  return;
}
#undef start
#undef buf

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
#define line_buf (*(char *)(frame_ + FRAME_OFF(0)))
#define line_char1 (*(char *)(frame_ + FRAME_OFF(1)))
#define entry_size (*(uint *)(frame_ + FRAME_OFF(256)))
void __cdecl text_section_index_build(iptr filename,uint pool_size)

{
  FILE *_File;
  long line_offset;
  char *line;
  size_t len;
  long *entry;
  i8 frame_[FRAME_OFF(264)] __attribute__((aligned(8)));  /* original stack frame */
  
  memblock_free((iptr)((u8 *)&g.d_006a5b38));
  memblock_init((iptr)((u8 *)&g.d_006a5b38),1,pool_size);
  text_section_index_valid = 0;
  text_section_index_count = 0;
  __getcwd(&text_section_index_path,0x104);
  crt_strcat(&text_section_index_path,&text_index_path_sep_str);
  crt_strcat(&text_section_index_path,filename);
  path_default_extension((iptr)((u8 *)&g.d_0062e508),(iptr)((u8 *)&g.d_0062cd24));
  _File = (FILE *)file_open_path((iptr)((u8 *)&g.d_0062e508),(iptr)((u8 *)&g.d_0062e618));
  if (_File == (FILE *)0x0) {
    text_section_index_path = 0;
  }
  else {
    while ((CRT_FEOF(_File)) == 0) {
      line_offset = _ftell(_File);
      line = _fgets(&line_buf,0xff,_File);
      if (line == (char *)0x0) break;
      str_strip_newline((iptr)&line_buf);
      str_trim((iptr)&line_buf);
      if (((line_buf == '@') && ('@' < line_char1)) && (line_char1 < '[')) {
        len = _strlen(&line_buf);
        entry_size = len + 5;
        if ((int)(uint)text_section_pool_free_bytes < (int)entry_size) break;
        entry = (long *)memblock_alloc((iptr)((u8 *)&g.d_006a5b38),entry_size);
        *entry = line_offset;
        crt_strcpy(entry + 1,&line_buf);
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
#undef line_buf
#undef line_char1
#undef entry_size

/* 004db450 auto */
#define text_section_index_count (*(i32 *)((u8 *)&g.d_0062e610))
#define text_section_index_valid (*(i32 *)((u8 *)&g.d_0062e60c))
void __cdecl text_section_index_free(void)

{
  text_section_index_valid = 0;
  text_section_index_count = 0;
  memblock_free((iptr)((u8 *)&g.d_006a5b38));
  return;
}
#undef text_section_index_count
#undef text_section_index_valid

/* 004db481 auto */
#define text_section_index_count (*(int *)((u8 *)&g.d_0062e610))
#define text_section_index_valid (*(int *)((u8 *)&g.d_0062e60c))
#define i (*(int *)(frame_ + FRAME_OFF(4)))
#define entry (*(char * *)(frame_ + FRAME_OFF(12)))
#define full_path (*(char (*)[260])(frame_ + FRAME_OFF(16)))
i32 __cdecl text_section_index_lookup(iptr filename,iptr section)

{
  char *next;
  int cmp;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (text_section_index_valid != 0) {
    __getcwd(full_path,0x104);
    crt_strcat(full_path,&text_lookup_path_sep_str);
    crt_strcat(full_path,filename);
    cmp = __strcmpi(full_path,&text_section_index_path);
    if (cmp == 0) {
      entry = text_section_index_base;
      for (i = 0; i < text_section_index_count; i++) {
        cmp = __strcmpi(entry + 4,(char *)section);
        next = entry + 4;
        if (cmp == 0) {
          return *(i32 *)entry;
        }
        while (entry = next, *entry != '\0') {
          next = entry + 1;
        }
        entry++;
      }
    }
  }
  return 0xffffffff;
}
#undef text_section_index_count
#undef text_section_index_valid
#undef i
#undef entry
#undef full_path

/* 00506448 auto */
#define city (*(uint *)(frame_ + FRAME_OFF(4)))
void __cdecl text_set_unit_info_args(iptr unit)

{
  iptr adjective;
  int x;
  int y;
  int city_here;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  text_clear();
  adjective = civ_get_adjective((int)units[unit].owner);
  text_append(adjective);
  if ((units[unit].flags & 0x2000) != 0) {
    text_append_space();
    text_append_label(0xd);
  }
  text_append_space();
  text_append_string_id(unit_types[units[unit].type].name);
  text_set_string_arg(0,(iptr)((u8 *)&g.d_00679640));
  text_clear();
  x = (int)units[unit].x;
  y = (int)units[unit].y;
  city_here = city_at(x,y);
  if (-1 < city_here) {
    text_append(city_here * 0x58 + (iptr)((u8 *)&cities + 32));
    text_append_space();
  }
  text_append_lparen();
  text_append_int(x);
  text_append_comma();
  text_append_int(y);
  text_append_rparen();
  if (city_here < 0) {
    x = city_find_nearest(x,y,-1,0xffffffff,-1);
    if (-1 < x) {
      text_append_space();
      text_append_lparen();
      text_append_label(0xb2);
      text_append_space();
      text_append(x * 0x58 + (iptr)((u8 *)&cities + 32));
      text_append_rparen();
    }
  }
  text_set_string_arg(1,(iptr)((u8 *)&g.d_00679640));
  text_clear();
  if (units[unit].home_city == -1) {
    city = 0xffffffff;
  }
  else {
    city = (uint)(byte)units[unit].home_city;
  }
  text_append_city_name(city);
  text_set_string_arg(2,(iptr)((u8 *)&g.d_00679640));
  return;
}
#undef city

/* 00511430 auto */
void __cdecl text_append_plus(void)

{
  str_append_plus((iptr)((u8 *)&g.d_00679640));
  return;
}

/* 005116f0 auto */
void __cdecl text_append_city_population(i32 city)

{
  str_append_city_population((iptr)((u8 *)&g.d_00679640),city);
  return;
}

/* 00553db0 auto */
int __cdecl str_find_bad_filename_char(iptr filename)

{
  __strupr((char *)filename);
  while ((*(char *)filename != '\0' && ((&filename_valid_chars)[*(char *)filename] != '\0'))) {
    filename++;
  }
  return (int)*(char *)filename;
}

/* 00564470 auto */
#define app_hinstance (*(HMODULE *)((u8 *)&g.d_006e4ff0))
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define attempt (*(int *)(frame_ + FRAME_OFF(4)))
#define cursor (*(char * *)(frame_ + FRAME_OFF(8)))
i32 __cdecl file_require_cdrom(iptr filename)

{
  iptr len;
  int found;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  GetModuleFileNameA(app_hinstance,&exe_dir_path,0x80);
  len = lstrlenA(&exe_dir_path);
  cursor = &exe_dir_path + len;
  do {
    if (cursor == (char *)0x0) break;
    cursor--;
  } while (*cursor != '\\');
  cursor[1] = '\0';
  do {
    for (attempt = 0; attempt < 2; attempt++) {
      found = file_find_fallback_drive(filename);
      if (found != 0) {
        return 1;
      }
    }
    popup_game_flags((iptr)((u8 *)&g.d_00633d5c),0x2000001);
  } while (dlg_help_pressed != 0);
  return 0;
}
#undef app_hinstance
#undef dlg_help_pressed
#undef attempt
#undef cursor

/* 00564574 auto */
#define fallback_drive_root (*(i8 *)((u8 *)&g.d_006ab680))
i8 * __cdecl file_get_fallback_drive(void)

{
  i8 *result;
  
  if (fallback_drive_root == '\0') {
    result = (i8 *)0x0;
  }
  else {
    result = &fallback_drive_root;
  }
  return result;
}
#undef fallback_drive_root

/* 0056459f auto */
#define fallback_drive_root (*(i8 *)((u8 *)&g.d_006ab680))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define drive (*(int *)(frame_ + FRAME_OFF(0)))
#define of_struct (*(_OFSTRUCT *)(frame_ + FRAME_OFF(4)))
#define drive_type (*(UINT *)(frame_ + FRAME_OFF(140)))
#define drive_strings (*(CHAR (*)[256])(frame_ + FRAME_OFF(144)))
#define drive_bit (*(uint *)(frame_ + FRAME_OFF(400)))
#define drive_root (*(char * *)(frame_ + FRAME_OFF(404)))
#define hfile (*(HFILE *)(frame_ + FRAME_OFF(408)))
i8 * __cdecl file_find_fallback_drive(iptr filename)

{
  UINT uMode;
  DWORD DVar1;
  i8 *result;
  i8 frame_[FRAME_OFF(416)] __attribute__((aligned(8)));  /* original stack frame */
  
  uMode = SetErrorMode(1);
  DVar1 = GetLogicalDrives();
  GetLogicalDriveStringsA(0x100,drive_strings);
  drive_root = drive_strings;
  drive = 0;
  do {
    if (0x19 < drive) {
LAB_005646e1:
      SetErrorMode(uMode);
      if (fallback_drive_root == '\0') {
        result = (i8 *)0x0;
      }
      else {
        result = &fallback_drive_root;
      }
      return result;
    }
    drive_bit = 1 << ((byte)drive & 0x1f);
    if ((DVar1 & drive_bit) != 0) {
      drive_type = GetDriveTypeA(drive_root);
      if (drive_type == 3) {
        text_clear();
        text_append((iptr)drive_root);
        text_append(filename);
        hfile = OpenFile(&text_buffer,&of_struct,0x4000);
        str_clear((iptr)((u8 *)&g.d_006ab680));
        fallback_drive_root = *drive_root;
        fallback_drive_root_end = 0;
        str_append((iptr)((u8 *)&g.d_006ab680),(iptr)((u8 *)&g.d_00633d6c));
        goto LAB_005646e1;
      }
      for (; *drive_root != '\0'; drive_root++) {
      }
      drive_root++;
    }
    drive++;
  } while( true );
}
#undef fallback_drive_root
#undef text_buffer
#undef drive
#undef of_struct
#undef drive_type
#undef drive_strings
#undef drive_bit
#undef drive_root
#undef hfile

/* 00564713 auto */
#define fallback_drive_root (*(char *)((u8 *)&g.d_006ab680))
#define alt_path (*(CHAR (*)[128])(frame_ + FRAME_OFF(0)))
#define base_name (*(i8 (*)[16])(frame_ + FRAME_OFF(128)))
#define of_struct (*(_OFSTRUCT *)(frame_ + FRAME_OFF(144)))
#define try_path (*(CHAR (*)[128])(frame_ + FRAME_OFF(280)))
#define name_offset (*(int *)(frame_ + FRAME_OFF(408)))
#define cursor (*(char * *)(frame_ + FRAME_OFF(412)))
#define result (*(HFILE *)(frame_ + FRAME_OFF(416)))
i32 __cdecl file_resolve_path(iptr path)

{
  char *next;
  char ch;
  iptr len;
  UINT uMode;
  i8 frame_[FRAME_OFF(424)] __attribute__((aligned(8)));  /* original stack frame */
  
  len = lstrlenA((LPCSTR)path);
  cursor = (char *)(path + len);
  name_offset = lstrlenA((LPCSTR)path);
  name_offset++;
  for (; (name_offset != 0 && (*cursor != '\\')); cursor--) {
    name_offset--;
  }
  cursor++;
  str_clear((iptr)base_name);
  str_clear((iptr)base_name);
  str_append((iptr)base_name,name_offset + path);
  uMode = SetErrorMode(1);
  str_clear((iptr)try_path);
  str_append((iptr)try_path,(iptr)((u8 *)&g.d_006ab600));
  str_append((iptr)try_path,(iptr)base_name);
  result = OpenFile(try_path,&of_struct,0x4000);
  if ((result == 0) || (result == -1)) {
    cursor = (char *)path;
    do {
      if (*cursor == '\0') break;
      next = cursor + 1;
      ch = *cursor;
      cursor = next;
    } while (ch != '\\');
    str_clear((iptr)alt_path);
    str_append((iptr)alt_path,(iptr)((u8 *)&g.d_006ab600));
    if (*cursor == '\0') {
      str_append((iptr)alt_path,path);
    }
    else {
      str_append((iptr)alt_path,(iptr)cursor);
    }
    result = OpenFile(alt_path,&of_struct,0x4000);
    if ((result == 0) || (result == -1)) {
      if (fallback_drive_root == '\0') {
        result = 0;
      }
      else {
        str_clear((iptr)try_path);
        str_append((iptr)try_path,(iptr)((u8 *)&g.d_006ab680));
        str_append((iptr)try_path,path);
        result = OpenFile(try_path,&of_struct,0x4000);
        if ((result == 0) || (result == -1)) {
          result = 0;
        }
        else {
          str_clear((iptr)alt_path);
          str_append((iptr)alt_path,(iptr)((u8 *)&g.d_006ab680));
          str_append((iptr)alt_path,path);
          str_clear(path);
          str_append(path,(iptr)alt_path);
          result = 1;
        }
      }
    }
    else {
      str_clear(path);
      str_append(path,(iptr)alt_path);
      result = 1;
    }
  }
  else {
    str_clear(path);
    str_append(path,(iptr)((u8 *)&g.d_006ab600));
    str_append(path,(iptr)base_name);
    result = 1;
  }
  SetErrorMode(uMode);
  return result;
}
#undef fallback_drive_root
#undef alt_path
#undef base_name
#undef of_struct
#undef try_path
#undef name_offset
#undef cursor
#undef result

/* 00564bf0 auto */
#define value (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl str_parse_int_prefixed(iptr text)

{
  char prefix;
  i32 upper;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(char *)text == '0') {
    upper = crt_toupper((uint)*(byte *)(text + 1));
    prefix = (char)upper;
    if (prefix == 'X') {
      value = str_parse_hex(text + 2);
    }
    else if (prefix == 'B') {
      value = str_parse_binary(text + 2);
    }
    else if (prefix == 'D') {
      value = _atoi((char *)(text + 2));
    }
    else {
      value = _atoi((char *)text);
    }
  }
  else {
    value = _atoi((char *)text);
  }
  return value;
}
#undef value

/* 00578abd auto */
#define cursor (*(char * *)(frame_ + FRAME_OFF(0)))
void __cdecl str_pipes_to_tabs(char *str)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (cursor = str; *cursor != '\0'; cursor++) {
    if (*cursor == '|') {
      *cursor = '\t';
    }
  }
  return;
}
#undef cursor

/* 00589fc9 auto */
#define result (*(i32 *)(frame_ + FRAME_OFF(4)))
#define i (*(iptr *)(frame_ + FRAME_OFF(8)))
#define line_buf (*(char (*)[80])(frame_ + FRAME_OFF(12)))
i32 __cdecl file_read_nth_line(iptr dest,iptr filename,int line_num)

{
  FILE *_File;
  char *line;
  size_t len;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  result = 1;
  _File = (FILE *)file_open_path(filename,(iptr)((u8 *)&g.d_00634840));
  if (_File != (FILE *)0x0) {
    for (i = 1; i <= line_num; i++) {
      if (((CRT_FEOF(_File)) != 0) ||
         (line = _fgets(line_buf,0x4c,_File), line == (char *)0x0)) goto LAB_0058a0bc;
    }
    for (i = 0; len = _strlen(line_buf), i < (int)len; i++) {
      if (line_buf[i] < ' ') {
        line_buf[i] = '\0';
      }
    }
    crt_strcpy(dest,line_buf);
    result = 0;
  }
LAB_0058a0bc:
  if (_File != (FILE *)0x0) {
    _fclose(_File);
  }
  return result;
}
#undef result
#undef i
#undef line_buf

/* 0058a80d auto */
#define buf (*(i8 (*)[1024])(frame_ + FRAME_OFF(0)))
#define src_file (*(FILE * *)(frame_ + FRAME_OFF(1024)))
#define bytes_read (*(size_t *)(frame_ + FRAME_OFF(1028)))
#define dest_file (*(FILE * *)(frame_ + FRAME_OFF(1032)))
void __cdecl file_copy(iptr src_path,iptr dest_path)

{
  int cmp;
  i8 frame_[FRAME_OFF(1040)] __attribute__((aligned(8)));  /* original stack frame */
  
  cmp = _strcmp((char *)src_path,(char *)dest_path);
  if (cmp != 0) {
    src_file = _fopen((char *)src_path,&file_copy_read_mode);
    if ((src_file == (FILE *)0x0) ||
       (dest_file = _fopen((char *)dest_path,&file_copy_write_mode), dest_file == (FILE *)0x0)) {
      MessageBoxA((HWND)0x0,s_Error_copying_file_00634954,(LPCSTR)0x0,0x10);
      if (src_file != (FILE *)0x0) {
        _fclose(src_file);
      }
    }
    else {
      while (bytes_read = _fread(buf,1,0x400,src_file), bytes_read != 0) {
        _fwrite(buf,1,bytes_read,dest_file);
      }
      _fclose(src_file);
      _fclose(dest_file);
    }
  }
  return;
}
#undef buf
#undef src_file
#undef bytes_read
#undef dest_file

/* 005bad40 auto */
#define value (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl str_parse_binary(iptr text)

{
  char ch;
  int upper;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  value = 0;
  while (*(char *)text != '\0') {
    ch = *(char *)text;
    text++;
    upper = crt_toupper((int)ch);
    if ((upper == 0x30) || (upper == 0x31)) {
      value = value * 2 + upper - 0x30;
    }
    else {
      for (; *(char *)text != '\0'; text++) {
      }
    }
  }
  return value;
}
#undef value

/* 005baeb0 auto */
void __cdecl text_set_surface(iptr surface)

{
  text_draw_surface = surface;
  return;
}

/* 005baec8 auto */
#define text_draw_font (*(iptr *)((u8 *)&g.d_006366ac))
void __cdecl text_set_font(iptr font)

{
  text_draw_font = font;
  return;
}
#undef text_draw_font

/* 005baee0 auto */
#define text_fg_color (*(i32 *)((u8 *)&g.d_006366b0))
#define text_shadow_color (*(i32 *)((u8 *)&g.d_006366b4))
#define text_shadow_dx (*(int *)((u8 *)&g.d_006366b8))
void __cdecl text_set_colors(i32 fg_color,i32 shadow_color,int shadow_dx,int shadow_dy)

{
  text_fg_color = fg_color;
  text_shadow_color = shadow_color;
  if (-1 < shadow_dx) {
    text_shadow_dx = shadow_dx;
  }
  if (-1 < shadow_dy) {
    text_shadow_dy = shadow_dy;
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
int __cdecl text_draw_shadowed(iptr surface,iptr text,int x,int y)

{
  int width;
  
  if (-1 < text_shadow_color) {
    gfx_set_text_color_index(text_shadow_color);
    surface_draw_text
              ((DibSurface *)surface,(iptr)text_draw_font,text,
               text_shadow_dx + text_fake_bold + x,text_shadow_dy + y,5);
  }
  if (-1 < text_fg_color) {
    gfx_set_text_color_index(text_fg_color);
    if (text_fake_bold != 0) {
      surface_draw_text
                ((DibSurface *)surface,(iptr)text_draw_font,text,x + 1,y,5);
    }
    surface_draw_text
              ((DibSurface *)surface,(iptr)text_draw_font,text,x,y,5);
  }
  width = font_text_width(text_draw_font,text);
  return x + width;
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
#define width2 (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl text_draw_centered(iptr surface,iptr text,int x,iptr y,int box_width)

{
  int total_width;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  width2 = font_text_width(text_draw_font,text);
  if (-1 < text_shadow_color) {
    if ((int)text_shadow_dx < 1) {
      width2 = width2 + ~text_shadow_dx + 1;
    }
    else {
      width2 += text_shadow_dx;
    }
  }
  total_width = width2 + text_fake_bold;
  text_draw_shadowed(surface,text,x + ((box_width >> 1) - (total_width >> 1)),y);
  return total_width;
}
#undef text_draw_font
#undef text_fake_bold
#undef text_shadow_color
#undef text_shadow_dx
#undef width2

/* 005bb0af auto */
#define text_draw_font (*(GameFont * *)((u8 *)&g.d_006366ac))
#define text_fake_bold (*(int *)((u8 *)&g.d_006366c0))
#define text_shadow_color (*(int *)((u8 *)&g.d_006366b4))
#define text_shadow_dx (*(uint *)((u8 *)&g.d_006366b8))
#define width2 (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl text_draw_right_aligned(iptr surface,iptr text,int x,i32 y,int box_width)

{
  int draw_x;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  width2 = font_text_width(text_draw_font,text);
  if (-1 < text_shadow_color) {
    if ((int)text_shadow_dx < 1) {
      width2 = width2 + ~text_shadow_dx + 1;
    }
    else {
      width2 += text_shadow_dx;
    }
  }
  draw_x = x + (box_width - (width2 + text_fake_bold));
  text_draw_shadowed(surface,text,draw_x,y);
  return draw_x;
}
#undef text_draw_font
#undef text_fake_bold
#undef text_shadow_color
#undef text_shadow_dx
#undef width2

/* 005c5520 auto */
void __cdecl res_free(i32 handle)

{
  res_free_impl(handle);
  return;
}

/* 005c5540 auto */
i32 __cdecl res_load(iptr res_type,i32 res_name)

{
  i32 handle;
  
  handle = res_load_impl(res_type,res_name);
  return handle;
}

/* 005c5560 auto */
i32 __cdecl res_lock(i32 handle)

{
  i32 data;
  
  data = res_lock_impl(handle);
  return data;
}

/* 005c5580 auto */
void __cdecl res_unlock(i32 handle)

{
  res_unlock_impl(handle);
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
  i32 result;
  
  result = file_map_close(this);
  return result;
}

/* 005d8270 auto */
#define full_path (*(char (*)[260])(frame_ + FRAME_OFF(0)))
i32 __cdecl file_obj_open_path(char *filename,iptr file_obj)

{
  char *sep;
  HFILE HVar2;
  i32 result;
  i8 frame_[FRAME_OFF(264)] __attribute__((aligned(8)));  /* original stack frame */
  
  sep = _strchr(filename,0x5c);
  if (sep == (char *)0x0) {
    __getcwd(full_path,0x104);
    crt_strcat(full_path,&file_path_backslash_str);
    crt_strcat(full_path,filename);
  }
  else {
    crt_strcpy(full_path,filename);
  }
  HVar2 = OpenFile(full_path,(LPOFSTRUCT)(file_obj + 8),0x4000);
  if (HVar2 == -1) {
    result = 0;
  }
  else {
    HVar2 = OpenFile(full_path,(LPOFSTRUCT)(file_obj + 8),2);
    *(HFILE *)(file_obj + 4) = HVar2;
    if (*(int *)(file_obj + 4) == -1) {
      *(i32 *)file_obj = 0;
      HVar2 = OpenFile(full_path,(LPOFSTRUCT)(file_obj + 8),0);
      *(HFILE *)(file_obj + 4) = HVar2;
      *(i32 *)(file_obj + 0x94) = 0;
      *(i32 *)(file_obj + 0x90) = 0;
      if (*(int *)(file_obj + 4) == -1) {
        *(i32 *)(file_obj + 4) = 0;
        return 0;
      }
    }
    else {
      *(i32 *)file_obj = 1;
    }
    result = 1;
  }
  return result;
}
#undef full_path

/* 005d83d6 auto */
uint __cdecl file_obj_create_path(LPCSTR filename,iptr file_obj)

{
  HANDLE handle;
  bool ok;
  
  handle = CreateFileA(filename,0xc0000000,0,(LPSECURITY_ATTRIBUTES)0x0,2,0x80,(HANDLE)0x0);
  *(HANDLE *)(file_obj + 4) = handle;
  ok = *(int *)(file_obj + 4) != -1;
  if (ok) {
    *(i32 *)file_obj = 1;
    *(i32 *)(file_obj + 0x94) = 0;
    *(i32 *)(file_obj + 0x90) = 0;
  }
  else {
    *(i32 *)(file_obj + 4) = 0;
    *(i32 *)file_obj = 0;
    *(i32 *)(file_obj + 0x94) = 0;
    *(i32 *)(file_obj + 0x90) = 0;
  }
  return (uint)ok;
}

/* 005d8476 auto */
i32 __cdecl file_obj_close_handle(iptr file_obj)

{
  i32 result;
  BOOL BVar2;
  
  if (*(int *)(file_obj + 4) == 0) {
    result = 0;
  }
  else {
    if ((*(int *)(file_obj + 0x94) != 0) || (*(int *)(file_obj + 0x90) != 0)) {
      file_obj_close_mapping(file_obj);
    }
    BVar2 = CloseHandle(*(HANDLE *)(file_obj + 4));
    if (BVar2 == 0) {
      result = 0;
    }
    else {
      *(i32 *)(file_obj + 4) = 0;
      result = 1;
    }
  }
  return result;
}

/* 005d84f6 auto */
#define bytes_read (*(DWORD *)(frame_ + FRAME_OFF(0)))
i32 __cdecl file_obj_read_bytes(iptr file_obj,LPVOID buf,DWORD size)

{
  i32 result;
  BOOL BVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(file_obj + 4) == 0) {
    result = 0;
  }
  else {
    BVar2 = ReadFile(*(HANDLE *)(file_obj + 4),buf,size,&bytes_read,(LPOVERLAPPED)0x0);
    if (BVar2 == 0) {
      result = 0;
    }
    else {
      result = 1;
    }
  }
  return result;
}
#undef bytes_read

/* 005d8622 auto */
i32 __cdecl file_obj_seek_rel(iptr file_obj,LONG offset)

{
  i32 result;
  DWORD DVar2;
  
  if (*(int *)(file_obj + 4) == 0) {
    result = 0;
  }
  else {
    DVar2 = SetFilePointer(*(HANDLE *)(file_obj + 4),offset,(PLONG)0x0,1);
    if (DVar2 == 0xffffffff) {
      result = 0;
    }
    else {
      result = 1;
    }
  }
  return result;
}

/* 005d8721 auto */
#define bytes_written (*(DWORD *)(frame_ + FRAME_OFF(0)))
i32 __cdecl file_obj_write_bytes(iptr file_obj,iptr buf,DWORD size)

{
  i32 result;
  BOOL BVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(file_obj + 4) == 0) {
    result = 0;
  }
  else if (*(int *)file_obj == 0) {
    dbg_log((iptr)((u8 *)&g.d_00638640));
    result = 0;
  }
  else {
    BVar2 = WriteFile(*(HANDLE *)(file_obj + 4),(LPCVOID)buf,size,&bytes_written,(LPOVERLAPPED)0x0);
    if (BVar2 == 0) {
      result = 0;
    }
    else {
      result = 1;
    }
  }
  return result;
}
#undef bytes_written

/* 005d881c auto */
#define ok (*(int *)(frame_ + FRAME_OFF(0)))
#define len (*(int *)(frame_ + FRAME_OFF(4)))
#define bytes_read (*(DWORD *)(frame_ + FRAME_OFF(8)))
#define dest (*(char * *)(frame_ + FRAME_OFF(12)))
#define ch (*(char (*)[4])(frame_ + FRAME_OFF(16)))
int __cdecl file_obj_read_line_impl(iptr file_obj,char *buf,int max_len)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  len = 0;
  dest = buf;
  *buf = '\0';
  if (*(int *)(file_obj + 4) == 0) {
    ok = 0;
  }
  else {
    ok = ReadFile(*(HANDLE *)(file_obj + 4),ch,1,&bytes_read,(LPOVERLAPPED)0x0);
    if (bytes_read == 0) {
      ok = 0;
    }
    else {
      while (((((ok != 0 && (bytes_read != 0)) && (ch[0] != '\n')) &&
              ((ch[0] != '\r' && (ch[0] != '\0')))) && (len < max_len))) {
        if (((ch[0] != '\r') && (ch[0] != '\n')) && (ch[0] != '\0')) {
          *dest = ch[0];
          dest++;
          len++;
        }
        ok = ReadFile(*(HANDLE *)(file_obj + 4),ch,1,&bytes_read,(LPOVERLAPPED)0x0);
      }
      *dest = '\0';
      while (((ok != 0 && (bytes_read != 0)) && ((ch[0] == '\n' || (ch[0] == '\r')))))
      {
        ok = ReadFile(*(HANDLE *)(file_obj + 4),ch,1,&bytes_read,(LPOVERLAPPED)0x0);
      }
      if (bytes_read != 0) {
        file_obj_seek_rel(file_obj,0xffffffff);
      }
    }
  }
  return ok;
}
#undef ok
#undef len
#undef bytes_read
#undef dest
#undef ch

/* 005d898e auto */
DWORD __cdecl file_obj_get_size_impl(iptr file_obj)

{
  DWORD DVar1;
  
  if (*(int *)(file_obj + 4) == 0) {
    DVar1 = 0;
  }
  else {
    DVar1 = GetFileSize(*(HANDLE *)(file_obj + 4),(LPDWORD)0x0);
    if (DVar1 == 0xffffffff) {
      dbg_log((iptr)((u8 *)&g.d_0063869c));
      DVar1 = 0;
    }
  }
  return DVar1;
}

/* 005d8ab8 auto */
i32 __cdecl file_obj_close_mapping(iptr file_obj)

{
  if ((*(int *)(file_obj + 0x94) != 0) && (*(int *)(file_obj + 0x90) != 0)) {
    UnmapViewOfFile(*(LPCVOID *)(file_obj + 0x90));
    *(i32 *)(file_obj + 0x90) = 0;
  }
  if (*(int *)(file_obj + 0x94) != 0) {
    CloseHandle(*(HANDLE *)(file_obj + 0x94));
    *(i32 *)(file_obj + 0x94) = 0;
  }
  return 0;
}

/* 005db140 auto */
#define res_dll_module_count (*(int *)((u8 *)&g.d_006387cc))
#define msg (*(i8 (*)[128])(frame_ + FRAME_OFF(4)))
HMODULE __cdecl res_dll_load_library(LPCSTR filename)

{
  HMODULE pHVar1;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  pHVar1 = LoadLibraryExA(filename,(HANDLE)0x0,2);
  if (pHVar1 == (HMODULE)0x0) {
    crt_strcpy(msg,s_Error__Resource_file_006387d0);
    crt_strcat(msg,filename);
    crt_strcat(msg,s_not_found__006387e8);
    dbg_log((iptr)msg);
    pHVar1 = (HMODULE)0x0;
  }
  else {
    *(HMODULE *)(&res_dll_modules + res_dll_module_count * 4) = pHVar1;
    res_dll_module_count++;
  }
  return pHVar1;
}
#undef res_dll_module_count
#undef msg

/* 005db1e0 auto */
void __cdecl res_free_impl(HGLOBAL handle)

{
  FreeResource(handle);
  return;
}

/* 005db1fa auto */
#define app_hinstance (*(HMODULE *)((u8 *)&g.d_006e4ff0))
#define res_dll_module_count (*(uint *)((u8 *)&g.d_006387cc))
#define hmodule2 (*(HMODULE *)(frame_ + FRAME_OFF(4)))
#define dll_index (*(uint *)(frame_ + FRAME_OFF(12)))
#define hrsrc (*(HRSRC *)(frame_ + FRAME_OFF(16)))
#define type_buf (*(CHAR *)(frame_ + FRAME_OFF(20)))
#define type_c1 (*(CHAR *)(frame_ + FRAME_OFF(21)))
#define type_c2 (*(CHAR *)(frame_ + FRAME_OFF(22)))
#define type_c3 (*(CHAR *)(frame_ + FRAME_OFF(23)))
#define type_nul (*(i8 *)(frame_ + FRAME_OFF(24)))
HGLOBAL __cdecl res_load_impl(CHAR *res_type,LPCSTR res_name)

{
  HGLOBAL handle;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  type_buf = *res_type;
  type_c1 = res_type[1];
  type_c2 = res_type[2];
  type_c3 = res_type[3];
  type_nul = 0;
  dll_index = 0xffffffff;
  hrsrc = FindResourceA(app_hinstance,res_name,&type_buf);
  if (hrsrc == (HRSRC)0x0) {
    dll_index = 0;
    while ((dll_index < res_dll_module_count &&
           (hrsrc = FindResourceA(*(HMODULE *)(&res_dll_modules + dll_index * 4),res_name,&type_buf),
           hrsrc == (HRSRC)0x0))) {
      dll_index++;
    }
  }
  if (hrsrc == (HRSRC)0x0) {
    handle = (HGLOBAL)0x0;
  }
  else {
    if (dll_index == 0xffffffff) {
      hmodule2 = app_hinstance;
    }
    else {
      hmodule2 = *(HMODULE *)(&res_dll_modules + dll_index * 4);
    }
    handle = LoadResource(hmodule2,hrsrc);
  }
  return handle;
}
#undef app_hinstance
#undef res_dll_module_count
#undef hmodule2
#undef dll_index
#undef hrsrc
#undef type_buf
#undef type_c1
#undef type_c2
#undef type_c3
#undef type_nul

/* 005db531 auto */
LPVOID __cdecl res_lock_impl(HGLOBAL handle)

{
  LPVOID data;
  
  data = LockResource(handle);
  return data;
}

/* 005db54b auto */
void __cdecl res_unlock_impl(i32 handle)

{
  return;
}

/* 005db55b auto */
#define res_dll_module_count (*(uint *)((u8 *)&g.d_006387cc))
#define i (*(uint *)(frame_ + FRAME_OFF(0)))
void __cdecl dll_unload(HMODULE hmodule)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (i = 0;
      (*(HMODULE *)(&res_dll_modules + i * 4) != hmodule && (i < res_dll_module_count));
      i = i + 1) {
  }
  if (i < res_dll_module_count) {
    for (; i < res_dll_module_count; i++) {
      *(i32 *)(&res_dll_modules + i * 4) = *(i32 *)(&res_dll_modules_elem1 + i * 4);
    }
    res_dll_module_count--;
    FreeLibrary(hmodule);
  }
  return;
}
#undef res_dll_module_count
#undef i
